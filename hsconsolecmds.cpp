#include "pch.h"

#include <stdlib.h>
#include <cstring>

#include "hstypes.h"
#include "hsdb.h"
#include "hscmds.h"
#include "hsobjects.h"
#include "hsutils.h"
#include "hsinterface.h"

HSPACE_COMMAND_PROTO(hscLockID)
HSPACE_COMMAND_PROTO(hscGunneryReport)
HSPACE_COMMAND_PROTO(hscConfigureWeapon)
HSPACE_COMMAND_PROTO(hscLoadWeapon)
HSPACE_COMMAND_PROTO(hscUnlockWeapons)
HSPACE_COMMAND_PROTO(hscChangeHeading)
HSPACE_COMMAND_PROTO(hscFireWeapon)
HSPACE_COMMAND_PROTO(hscSetConsPower)
HSPACE_COMMAND_PROTO(hscTargetReport)
HSPACE_COMMAND_PROTO(hscUnload)
HSPACE_COMMAND_PROTO(hscSetAutoload)
HSPACE_COMMAND_PROTO(hscSetAutoRotate) HSPACE_COMMAND_PROTO(hscTargetSystem)
// The hsConCommandArray holds all externally callable 
// @console commands.
    HSPACE_COMMAND hsConCommandArray[] = {
        {"AUTOLOAD", hscSetAutoload, HCP_ANY}
        ,
        {"AUTOROTATE", hscSetAutoRotate, HCP_ANY}
        ,
        {"CONFIGURE", hscConfigureWeapon, HCP_ANY}
        ,
        {"FIRE", hscFireWeapon, HCP_ANY}
        ,
        {"GREP", hscGunneryReport, HCP_ANY}
        ,
        {"HEAD", hscChangeHeading, HCP_ANY}
        ,
        {"LOAD", hscLoadWeapon, HCP_ANY}
        ,
        {"LOCK", hscLockID, HCP_ANY}
        ,
        {"POWER", hscSetConsPower, HCP_ANY}
        ,
        {"QREP", hscTargetReport, HCP_ANY}
        ,
        {"TARGET", hscTargetSystem, HCP_ANY}
        ,
        {"UNLOAD", hscUnload, HCP_ANY}
        ,
        {"UNLOCK", hscUnlockWeapons, HCP_ANY}
        ,
        {NULL, NULL, 0}
    };

// Allows a console to lock on to a target with a given
// contact ID on sensors.
HSPACE_COMMAND_HDR(hscLockID)
{
    CHSConsole *cConsole;
    HS_DBREF dbUser;

    // player is the HS_DBREF of the console issuing the command
    cConsole = dbHSDB.FindConsole(player);
    if (!cConsole)
    {
        hsInterface.Notify(player, "Go away!  You're not an HSpace console.");
        return;
    }

    // Grab the user of the console
    dbUser = hsInterface.ConsoleUser(player);

    // Is the console online?
    if (!cConsole->IsOnline())
    {
        hsStdError(dbUser,
                   hsInterface.HSPrintf("%s is currently powered down.",
                                        hsInterface.GetName(player)));
        return;
    }

    // Proper command usage.
    if (!arg_left || !*arg_left)
    {
        hsStdError(dbUser, "You must specify a target ID to lock onto.");
        return;
    }

    cConsole->LockTargetID(dbUser, atoi(arg_left));
}

// Allows a console to lock on to a target with a given
// contact ID on sensors.
HSPACE_COMMAND_HDR(hscGunneryReport)
{
    CHSConsole *cConsole;
    HS_DBREF dbUser;

    // player is the HS_DBREF of the console issuing the command
    cConsole = dbHSDB.FindConsole(player);
    if (!cConsole)
    {
        hsInterface.Notify(player, "Go away!  You're not an HSpace console.");
        return;
    }

    // Grab the user of the console
    dbUser = hsInterface.ConsoleUser(player);

    // Is the console online?
    if (!cConsole->IsOnline())
    {
        hsStdError(dbUser,
                   hsInterface.HSPrintf("%s is currently powered down.",
                                        hsInterface.GetName(player)));
        return;
    }

    cConsole->GiveGunneryReport(dbUser);
}

// Allows a player to configure a given weapon on the console
HSPACE_COMMAND_HDR(hscConfigureWeapon)
{
    CHSConsole *cConsole;
    HS_DBREF dbUser;
    int weapon;
    int type;

    // player is the HS_DBREF of the console issuing the command
    cConsole = dbHSDB.FindConsole(player);
    if (!cConsole)
    {
        hsInterface.Notify(player, "Go away!  You're not an HSpace console.");
        return;
    }

    // Grab the user of the console
    dbUser = hsInterface.ConsoleUser(player);

    // Is the console online?
    if (!cConsole->IsOnline())
    {
        hsStdError(dbUser,
                   hsInterface.HSPrintf("%s is currently powered down.",
                                        hsInterface.GetName(player)));
        return;
    }

    // Proper command usage?
    if (!arg_left || !*arg_left || !arg_right || !*arg_right)
    {
        hsInterface.Notify(dbUser,
                           "You must specify a weapon ID and a munitions ID.");
        return;
    }
    weapon = atoi(arg_left);
    type = atoi(arg_right);

    cConsole->ConfigureWeapon(dbUser, weapon, type);
}

// Allows a player to load a specified weapon.
HSPACE_COMMAND_HDR(hscLoadWeapon)
{
    CHSConsole *cConsole;
    HS_DBREF dbUser;
    int weapon;

    // player is the HS_DBREF of the console issuing the command
    cConsole = dbHSDB.FindConsole(player);
    if (!cConsole)
    {
        hsInterface.Notify(player, "Go away!  You're not an HSpace console.");
        return;
    }

    // Grab the user of the console
    dbUser = hsInterface.ConsoleUser(player);

    // Is the console online?
    if (!cConsole->IsOnline())
    {
        hsStdError(dbUser,
                   hsInterface.HSPrintf("%s is currently powered down.",
                                        hsInterface.GetName(player)));
        return;
    }

    weapon = atoi(arg_left);

    // Tell the console to load a weapon
    cConsole->LoadWeapon(dbUser, weapon);
}

// Allows a player to unlock the weapons from a target.
HSPACE_COMMAND_HDR(hscUnlockWeapons)
{
    CHSConsole *cConsole;
    HS_DBREF dbUser;

    // player is the HS_DBREF of the console issuing the command
    cConsole = dbHSDB.FindConsole(player);
    if (!cConsole)
    {
        hsInterface.Notify(player, "Go away!  You're not an HSpace console.");
        return;
    }

    // Grab the user of the console
    dbUser = hsInterface.ConsoleUser(player);

    // Is the console online?
    if (!cConsole->IsOnline())
    {
        hsStdError(dbUser,
                   hsInterface.HSPrintf("%s is currently powered down.",
                                        hsInterface.GetName(player)));
        return;
    }

    // Tell the console to unlock weapons.
    cConsole->UnlockWeapons(dbUser);
}

// Allows a player to turn the console (turret)
HSPACE_COMMAND_HDR(hscChangeHeading)
{
    CHSConsole *cConsole;
    HS_DBREF dbUser;
    int xy, z;

    // player is the HS_DBREF of the console issuing the command
    cConsole = dbHSDB.FindConsole(player);
    if (!cConsole)
    {
        hsInterface.Notify(player, "Go away!  You're not an HSpace console.");
        return;
    }

    // Grab the user of the console
    dbUser = hsInterface.ConsoleUser(player);

    // Is the console online?
    if (!cConsole->IsOnline())
    {
        hsStdError(dbUser,
                   hsInterface.HSPrintf("%s is currently powered down.",
                                        hsInterface.GetName(player)));
        return;
    }

    // Determine how to change the angles
    if (!arg_left || !*arg_left)
        xy = HSNOTHING;
    else
        xy = atoi(arg_left);

    if (!arg_right || !*arg_right)
        z = -91;                // Because -1 is a possible angle
    else
        z = atoi(arg_right);

    // Tell the console to change the heading
    cConsole->ChangeHeading(dbUser, xy, z);
}

// Allows a player to fire a given weapon.
HSPACE_COMMAND_HDR(hscFireWeapon)
{
    CHSConsole *cConsole;
    HS_DBREF dbUser;
    HS_INT32 HitValue = -1;

    // player is the HS_DBREF of the console issuing the command
    cConsole = dbHSDB.FindConsole(player);
    if (!cConsole)
    {
        hsInterface.Notify(player, "Go away!  You're not an HSpace console.");
        return;
    }

    // Grab the user of the console
    dbUser = hsInterface.ConsoleUser(player);

    // Is the console online?
    if (!cConsole->IsOnline())
    {
        hsStdError(dbUser,
                   hsInterface.HSPrintf("%s is currently powered down.",
                                        hsInterface.GetName(player)));
        return;
    }

    if (strlen(arg_right))
    {
        HitValue = atoi(arg_right);
        if (HitValue > 1)
        {
            HitValue = -1;
        }
        else if (HitValue < 0)
        {
            HitValue = -1;
        }
        cConsole->FireWeapon(dbUser, atoi(arg_left), HitValue);
    }
    else
    {
        // Tell the console to unlock weapons.
        cConsole->FireWeapon(dbUser, atoi(arg_left), HitValue);
    }
}

// Allows a player to power up/down the console.
HSPACE_COMMAND_HDR(hscSetConsPower)
{
    CHSConsole *cConsole;
    HS_DBREF dbUser;

    // player is the HS_DBREF of the console issuing the command
    cConsole = dbHSDB.FindConsole(player);
    if (!cConsole)
    {
        hsInterface.Notify(player, "Go away!  You're not an HSpace console.");
        return;
    }

    // Grab the user of the console
    dbUser = hsInterface.ConsoleUser(player);

    // Command usage?
    if (!arg_left || !*arg_left)
    {
        hsInterface.Notify(dbUser, "You must specify 1/0 for power status.");
        return;
    }

    int stat;
    stat = atoi(arg_left);

    if (!stat)
        cConsole->PowerDown(dbUser);
    else
        cConsole->PowerUp(dbUser);
}

// Gives a target (quick) report to the player
HSPACE_COMMAND_HDR(hscTargetReport)
{
    CHSConsole *cConsole;
    HS_DBREF dbUser;

    // player is the HS_DBREF of the console issuing the command
    cConsole = dbHSDB.FindConsole(player);
    if (!cConsole)
    {
        hsInterface.Notify(player, "Go away!  You're not an HSpace console.");
        return;
    }

    // Grab the user of the console
    dbUser = hsInterface.ConsoleUser(player);

    // Is the console online?
    if (!cConsole->IsOnline())
    {
        hsStdError(dbUser,
                   hsInterface.HSPrintf("%s is currently powered down.",
                                        hsInterface.GetName(player)));
        return;
    }

    cConsole->GiveTargetReport(dbUser);
}

// Allows a player to unload a given weapon
HSPACE_COMMAND_HDR(hscUnload)
{
    CHSConsole *cConsole;
    HS_DBREF dbUser;

    // player is the HS_DBREF of the console issuing the command
    cConsole = dbHSDB.FindConsole(player);
    if (!cConsole)
    {
        hsInterface.Notify(player, "Go away!  You're not an HSpace console.");
        return;
    }

    // Grab the user of the console
    dbUser = hsInterface.ConsoleUser(player);

    // Is the console online?
    if (!cConsole->IsOnline())
    {
        hsStdError(dbUser,
                   hsInterface.HSPrintf("%s is currently powered down.",
                                        hsInterface.GetName(player)));
        return;
    }

    cConsole->UnloadWeapon(dbUser, atoi(arg_left));
}

// Toggles the autoloading for the console.
HSPACE_COMMAND_HDR(hscSetAutoload)
{
    CHSConsole *cConsole;
    HS_DBREF dbUser;

    // player is the HS_DBREF of the console issuing the command
    cConsole = dbHSDB.FindConsole(player);
    if (!cConsole)
    {
        hsInterface.Notify(player, "Go away!  You're not an HSpace console.");
        return;
    }

    // Grab the user of the console
    dbUser = hsInterface.ConsoleUser(player);

    // Is the console online?
    if (!cConsole->IsOnline())
    {
        hsStdError(dbUser,
                   hsInterface.HSPrintf("%s is currently powered down.",
                                        hsInterface.GetName(player)));
        return;
    }

    HS_BOOL8 stat;
    stat = atoi(arg_left) == 0 ? false : true;
    cConsole->SetAutoload(dbUser, stat);
}

// Toggles the autorotate for the console.
HSPACE_COMMAND_HDR(hscSetAutoRotate)
{
    CHSConsole *cConsole;
    HS_DBREF dbUser;

    // player is the HS_DBREF of the console issuing the command
    cConsole = dbHSDB.FindConsole(player);
    if (!cConsole)
    {
        hsInterface.Notify(player, "Go away!  You're not an HSpace console.");
        return;
    }

    // Grab the user of the console
    dbUser = hsInterface.ConsoleUser(player);

    // Is the console online?
    if (!cConsole->IsOnline())
    {
        hsStdError(dbUser,
                   hsInterface.HSPrintf("%s is currently powered down.",
                                        hsInterface.GetName(player)));
        return;
    }

    HS_BOOL8 stat;
    stat = atoi(arg_left) == 0 ? false : true;
    cConsole->SetAutoRotate(dbUser, stat);
}

// Allows the player to target a given system on an enemy ship.
HSPACE_COMMAND_HDR(hscTargetSystem)
{
    CHSConsole *cConsole;
    HS_DBREF dbUser;
    int type;

    // player is the HS_DBREF of the console issuing the command
    cConsole = dbHSDB.FindConsole(player);
    if (!cConsole)
    {
        hsInterface.Notify(player, "Go away!  You're not an HSpace console.");
        return;
    }

    // Grab the user of the console
    dbUser = hsInterface.ConsoleUser(player);

    // Is the console online?
    if (!cConsole->IsOnline())
    {
        hsStdError(dbUser,
                   hsInterface.HSPrintf("%s is currently powered down.",
                                        hsInterface.GetName(player)));
        return;
    }

    // Find the type of system based on the name
    if (!_stricmp(arg_left, "none"))
        type = HSS_NOTYPE;
    else
        type = hsGetEngSystemType(arg_left);

    cConsole->SetSystemTarget(dbUser, type);
}
