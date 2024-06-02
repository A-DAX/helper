#ifndef HELPER_H
#define HELPER_H

/*****************************************************************************\
 * @brief ___FUNCTION_NAME_CHOOSER is a macro that receive some arguments and
 *     only select the 10th (so FN9 here).
 *     Used with ___FUNCTION_NAME_FOR_ARGUMENT_NUMBER, this function received
 *     all the argument for the final function at the left, and then, all
 *     the possible function name at the right.
 *     This way, the correct name will be at the correct position
 *     THIS MACRO SHOULD NEVER BE CALLED DIRECTLY EXCEPT INSIDE THIS FILE
 * @param FNX for FUNCTION_ROOT_NAME_X when X is a number between 0 and 9
 *     both included
 * @param __VA_ARGS__ a way to escape the function name that do not have
 *     enough parameters
\*****************************************************************************/
#define ___FUNCTION_NAME_CHOOSER(FN0, FN1, FN2, FN3, FN4, FN5, FN6, FN7, FN8, FN9, ...) FN9

/******************************************************************************\
 * @brief ___PARENTHESIS_REMOVER is a macro that simply remove the first and
 *     last parenthesis of the ARGUMENT_WITH_PARENTHESIS
 *     THIS MACRO SHOULD NEVER BE CALLED DIRECTLY EXCEPT INSIDE THIS FILE
 * @param ARGUMENT_WITH_PARENTHESIS a block of arguments with parenthesis
\*****************************************************************************/
#define ___PARENTHESIS_REMOVER(ARGUMENT_WITH_PARENTHESIS) ___FUNCTION_NAME_CHOOSER ARGUMENT_WITH_PARENTHESIS

/*****************************************************************************\
 * @brief ___FUNCTION_NAME_FOR_ARGUMENT_NUMBER is a macro that generate
 *     all the possible function or macro name for the given root name and
 *     then, call the ___PARENTHESIS_REMOVER that will call the
 *     ___FUNCTION_NAME_CHOOSER macro with the arguments in first position.
 *     This way, the wanted name will be at the 10th position (FN9) of the
 *     ___FUNCTION_NAME_CHOOSER and then, be selected
 *     THIS MACRO SHOULD NEVER BE CALLED DIRECTLY EXCEPT INSIDE THIS FILE
 * @param F for the FUNCTION_ROOT_NAME the root name of the final
 *     fonctions or macro
\*****************************************************************************/
#define ___FUNCTION_NAME_FOR_ARGUMENT_NUMBER(F, ...) ___PARENTHESIS_REMOVER((__VA_ARGS__, \
            F##_9, F##_8, F##_7, F##_6, F##_5, F##_4, F##_3, F##_2, F##_1, ))

/*****************************************************************************\
 * @brief ___ZERO_ARGUMENT_REPLACEMENT is a macro that, when called
 *     is replaced by a lot of coma (9) and a FUNCTION_ROOT_NAME_0
 *     Please note that this macro as no result when no parameter are given
 *     THIS MACRO SHOULD NEVER BE CALLED DIRECTLY EXCEPT INSIDE THIS FILE
 * @param FUNCTION_ROOT_NAME: the root name of the final fonctions or macro
\*****************************************************************************/
#define ___ZERO_ARGUMENT_REPLACEMENT(FUNCTION_ROOT_NAME) ,,,,,,,,,FUNCTION_ROOT_NAME##_0

/*****************************************************************************\
 * @brief ___ZERO_ARGUMENT_DECORATOR is a macro that call the macro
 *     ___FUNCTION_NAME_FOR_ARGUMENT_NUMBER in a way that support the case
 *     when there is zero argument given
 *     THIS MACRO SHOULD NEVER BE CALLED DIRECTLY EXCEPT INSIDE THIS FILE
 * @param FUNCTION_ROOT_NAME: the root name of the final fonctions or macro
 * @param __VA_ARGS__: the variable number of argument givent to the function
 *     even non optional arguments are included
\*****************************************************************************/
#define ___ZERO_ARGUMENT_DECORATOR(FUNCTION_ROOT_NAME, ...)\
    ___FUNCTION_NAME_FOR_ARGUMENT_NUMBER(FUNCTION_ROOT_NAME, ___ZERO_ARGUMENT_REPLACEMENT __VA_ARGS__ (FUNCTION_ROOT_NAME))

/*****************************************************************************\
 * @brief OPTIONAL_PARAMETER_ADDRESSER is a macro that give the possibility to
 *     acess to different code generation depending on the number of
 *     parameter given.
 *     Depending of the number of parameter given, the function
 *     ___ZERO_ARGUMENT_DECORATOR will transform to FUNCTION_ROOT_NAME_1 or
 *     FUNCTION_ROOT_NAME_2, ...
 *     Up to 9 parameter can be used, for more, the helper should be modified
 * @param FUNCTION_ROOT_NAME: the root name of the final fonctions or macro
 * @param __VA_ARGS__: the variable number of argument givent to the function
 *     even non optional arguments are included
\*****************************************************************************/
#define OPTIONAL_PARAMETER_ADDRESSER(FUNCTION_ROOT_NAME, ...) ___ZERO_ARGUMENT_DECORATOR(FUNCTION_ROOT_NAME, __VA_ARGS__)(__VA_ARGS__)

/*****************************************************************************\
 * @brief ___FUNCTION_BY_KEYWORD only concatenate the first and third
 *    parameter resulting in the name of the definition that shall replace
 *    this call (and so, be called)
 *    THIS MACRO SHOULD NEVER BE CALLED DIRECTLY EXCEPT INSIDE THIS FILE
 * @param FUNCTION_ROOT_NAME: the root name of the final fonctions or macro
 * @param USELESS: something that can be empty but is never used
 * @param KEYWORD: the given keyword or ALL if none given
 * @param __VA_ARGS__: if a keyword is given, capture and remove the default
 *    keyword: 'ALL'
\*****************************************************************************/
#define ___FUNCTION_BY_KEYWORD(FUNCTION_ROOT_NAME, USELESS, KEYWORD, ...)\
    FUNCTION_ROOT_NAME##_##KEYWORD

/*****************************************************************************\
 * @brief ___DELAYED_FUNCTION_BY_KEYWORD only call ___FUNCTION_BY_KEYWORD
 *    but ensure in the process that FUNCTION_ROOT_NAME##_USE_##KEYWORD from
 *    KEYWORD_ADRESSER's definition is correctly replaced with the correct
 *    value if given.
 *    THIS MACRO SHOULD NEVER BE CALLED DIRECTLY EXCEPT INSIDE THIS FILE
 * @param FUNCTION_ROOT_NAME: the root name of the final fonctions or macro
 * @param USELESS_AND_MAYBE_KEYWORD: the replacement of
 *    FUNCTION_ROOT_NAME_USE_KEYWORD wich shall be SOMETHING, KEYWORD
 * @param ALL the default keyword
\*****************************************************************************/
#define ___DELAYED_FUNCTION_BY_KEYWORD(FUNCTION_ROOT_NAME, USELESS_AND_MAYBE_KEYWORD, ALL)\
    ___FUNCTION_BY_KEYWORD(FUNCTION_ROOT_NAME, USELESS_AND_MAYBE_KEYWORD, ALL)

/*****************************************************************************\
 * @brief KEYWORD_ADRESSER is a macro that give the possibility to
 *     acess to different code generation depending on the given keyword.
 *     Also gives the possibility of a default function with the 'ALL'
 *     keyword.
 *     To define a function for a specific keyword, one shall define:
 *     FUNCTION_ROOT_NAME_USE_KEYWORD ANYTHING,KEYWORD
 *     (keyword is case sensitive)
 *     Then, the desired generated code shall be defined under:
 *     FUNCTION_ROOT_NAME_KEYWORD
 *     If it possible that something else than a defined keyword is given,
 *     the default generated code shall be defined under:
 *     FUNCTION_ROOT_NAME_ALL
 *     All macro functions shall have the same number of parameter
 *     (from 0 to far too much)
 * @note CAN BE EASILY COMBINED WITH OPTIONAL_PARAMETER_ADDRESSER
 * @param FUNCTION_ROOT_NAME: the root name of the final fonctions or macro
 * @param KEYWORD: the keyword
 * @param __VA_ARGS__: the arguments for the final generated function
\*****************************************************************************/
#define KEYWORD_ADRESSER(FUNCTION_ROOT_NAME, KEYWORD, ...)\
    ___DELAYED_FUNCTION_BY_KEYWORD(FUNCTION_ROOT_NAME, FUNCTION_ROOT_NAME##_USE_##KEYWORD, ALL)(__VA_ARGS__)

#endif // HELPER_H
