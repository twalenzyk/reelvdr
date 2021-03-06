
//***************************************************************************
// Includes
//***************************************************************************

#include <vdr/menuitems.h>
#include "setupmenu.h"
#include <ctype.h>               // isdigit

//***************************************************************************
// Object
//***************************************************************************

PinSetupMenu::PinSetupMenu()
{
   static const char* trProtectionModes[cPinPlugin::apmCount] = { 0 };

   hidePinCode = yes;
   // hidePinCode = no;

   if (hidePinCode)
   {
      for (int i = 0; i < cPinPlugin::sizePinCode; i++)
         pinCode[i] = '*';

      pinCode[cPinPlugin::sizePinCode] = 0;
   }
   else
   {
      strcpy(pinCode, cPinPlugin::pinCode);
   }

   skipChannelSilent = cPinPlugin::skipChannelSilent;
   pinResetTime = cPinPlugin::pinResetTime;
   autoMenuOpen = cPinPlugin::autoMenuOpen;
   autoProtectionMode = cPinPlugin::autoProtectionMode;

   // translate protection modes

   if (!trProtectionModes[0])
      for (int i = 0; i < cPinPlugin::apmCount; i++)
         trProtectionModes[i] = tr(cPinPlugin::autoProtectionModes[i]);

   if (hidePinCode)
      Add(new cMenuEditStrItem(tr("Pin code"), pinCode, cPinPlugin::sizePinCode+TB, "0123456789*"));
   else
      Add(new cMenuEditNumItem(tr("Pin code"), pinCode, cPinPlugin::sizePinCode, false));

   Add(new cMenuEditBoolItem(tr("Skip protected channel silent"), &skipChannelSilent));
   Add(new cMenuEditBoolItem(tr("Open menu after pin request"), &autoMenuOpen));
   Add(new cMenuEditIntItem(tr("Pin inactivity time [min]"), &pinResetTime, 0, 5*60));  // max 5 hour
	Add(new cMenuEditStraItem(tr("Autoprotection of recordings"), &autoProtectionMode, 
                             cPinPlugin::apmCount, trProtectionModes));
}

PinSetupMenu::~PinSetupMenu()
{
   // nothing yet
}

//***************************************************************************
// Store
//***************************************************************************

void PinSetupMenu::Store(void)
{
   int i = 0;
   int pinValid = yes;
   
   if (hidePinCode)
   {
      // store only numerical pin codes
      
      if (strcmp(pinCode, "****") != 0)
      {
         while (pinCode[i])
         {
            if (!isdigit(pinCode[i++]))
            {
               i--;
               pinCode[i] = 0;
               break;
            }
         }

         if (i < 2)
         {
            Skins.Message(mtError, tr("Ignoring invalid pin"));
            pinValid = no;
         }
      }
      else
         pinValid = no;
   }
   
   if (pinValid)
   {
      strncpy(cPinPlugin::pinCode, pinCode, cPinPlugin::sizePinCode);
      cPinPlugin::pinCode[cPinPlugin::sizePinCode] = 0;
      SetupStore("pinCode", cPinPlugin::pinCode);
   }
   
   cPinPlugin::skipChannelSilent = skipChannelSilent;
   cPinPlugin::pinResetTime = pinResetTime;
   cPinPlugin::autoMenuOpen = autoMenuOpen;
   cPinPlugin::autoProtectionMode = autoProtectionMode;

   SetupStore("skipChannelSilent", skipChannelSilent);
   SetupStore("pinResetTime", pinResetTime);
   SetupStore("autoMenuOpen", autoMenuOpen);
   SetupStore("autoProtectionMode", autoProtectionMode);
}
