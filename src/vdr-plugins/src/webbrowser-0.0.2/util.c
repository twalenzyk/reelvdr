/****************************************************************************
 * copied from setup-plugin
 ****************************************************************************/

#include <string.h>
#include <stdio.h>
#include "util.h"
#include "common.h"

Util::Util()
{
}


Util::~Util()
{
}

static const char *undefStr = "undefined";
static const char *boolStr = "bool";
static const char *textStr = "text";
static const char *numTextStr = "numtext";
static const char *hexStr = "hex";
static const char *ipStr = "ip";
static const char *numberStr = "number";
static const char *selectionStr = "selection";


static const char *trueStr = "true";
static const char *falseStr = "false";
static const char *yesStr = "yes";
static const char *noStr = "no";


char *Util::Strdupnew(const char *str)
{
    return (str ? strcpy(new char[strlen(str) + 1], str) : 0);
}

char *Util::Strdupnew(const char *str, int size)
{
    char *result = NULL;
    if (str != NULL)
    {
        result = strncpy(new char[size + 1], str, size);
        result[size] = '\0';
    }

    return (result);
}


char *Util::Strdupnew(const char *prefix, const char *str)
{
    char *newStr = NULL;

    if (str != NULL && prefix != NULL)
    {
        int len = strlen(prefix) + strlen(str);
        newStr = new char[(len + 1)];
        sprintf(newStr, "%s%s", prefix, str);
    }
    return (newStr);
}


/**
 * check id the given string represenst a bool value
 * @param string string to compare for bool representation
 * @param flag corresponding bool value
 * @return false if error was detected
 */
bool Util::isBool(const char *string, bool & flag)
{
    bool ok = true;

    if (string != NULL)
    {
        if (strcmp(string, trueStr) == 0 || strcmp(string, yesStr) == 0)
            flag = true;
        else if (strcmp(string, falseStr) == 0 || strcmp(string, noStr) == 0)
            flag = false;
        else
            ok = false;
    }
    else
        ok = false;

    if (!ok)
        d(printf("Illegal Bool value %s found\n", string)) return (ok);
}

bool Util::isBool(const char *string, int &flag)
{
    bool ok = true;
    bool boolVal;

    if (isBool(string, boolVal))
    {
        if (boolVal)
            flag = true;
        else
            flag = false;
    }

    return (ok);
}


/**
 * check id the given string represenst a Type value
 *
 * known types are "text", "bool", "number", "numtext" "ip"
 * @param string string to compare for type representation
 * @param typ corresponding type value
 * @return false if error was detected
 */
bool Util::isType(const char *string, Util::Type & type)
{
    bool ok = true;

    if (string != NULL)
    {
        if (strcmp(string, boolStr) == 0)
            type = Util::BOOL;
        else if (strcmp(string, textStr) == 0)
            type = Util::TEXT;
        else if (strcmp(string, numTextStr) == 0)
            type = Util::NUMBER_TEXT;
        else if (strcmp(string, hexStr) == 0)
            type = Util::HEX;
        else if (strcmp(string, numberStr) == 0)
            type = Util::NUMBER;
        else if (strcmp(string, ipStr) == 0)
            type = Util::IP;
        else if (strcmp(string, selectionStr) == 0)
            type = Util::SELECTION;
        else
            ok = false;
    }
    else
        ok = false;

    if (!ok)
        d(printf("Illegal Type value %s found\n", string)) return (ok);
}


/**
 * 
 * @param string 
 * @param number 
 * @return 
 */
bool Util::isNumber(const char *string, int &number)
{
    bool ok = true;
    number = 0;

    if (string != NULL)
    {
        int len = strlen(string);
        for (int i = 0; i < len && ok == true; i++)
            if (string[i] < '0' || string[i] > '9')
                ok = false;
            else
                number = number * 10 + (string[i] - '0');
    }
    else
        ok = false;

    return (ok);

}


/**
 * Returns the strung representation of given type
 * @param type 
 * @return 
 */
const char *Util::boolToStr(bool val)
{
    const char *result;

    if (val == true)
        result = yesStr;
    else
        result = noStr;


    return (result);
}



/**
 * Returns the strung representation of given type
 * @param type 
 * @return 
 */
const char *Util::typeToStr(Type type)
{
    const char *result = undefStr;
    switch (type)
    {
    case BOOL:
        result = boolStr;
        break;
    case TEXT:
        result = textStr;
        break;
    case NUMBER_TEXT:
        result = numTextStr;
        break;
    case HEX:
        result = hexStr;
        break;
    case NUMBER:
        result = numberStr;
        break;
    case IP:
        result = ipStr;
        break;
    case SELECTION:
        result = selectionStr;
        break;
    case UNDEFINED:
        result = undefStr;
        break;
    }
    return (result);
}
