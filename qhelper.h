#ifndef QHELPER_H
#define QHELPER_H

#include "helper.h"

#define AxTYPED_EQ_COMPARATOR_USE_QVariant ,QVariant
#define AxTYPED_EQ_COMPARATOR_QVariant(A, B) ((A.typeId() == B.typeId()) && (A == B))
#define AxTYPED_EQ_COMPARATOR_ALL(A, B) (A == B)
#define AxTYPED_EQ_COMPARATOR(type, A, B) KEYWORD_ADRESSER(AxTYPED_EQ_COMPARATOR, type, A, B)

#define ___AxPROPERTY__2(type, name)\
    Q_PROPERTY(type name READ name CONSTANT)\
public:\
    const type& name() const {\
        return m_##name;\
    }\
private:\
    type m_##name {};

#define ___AxPROPERTY__3(type, name, setter)\
public:\
    Q_PROPERTY(type name READ name WRITE setter NOTIFY name##Changed)\
public:\
    Q_SIGNAL void name##Changed();\
public:\
    const type& name() const {\
        return m_##name;\
    };\
    void setter(const type& newValue) {\
        if (AxTYPED_EQ_COMPARATOR(type, m_##name, newValue)) return;\
        m_##name = newValue;\
        emit name##Changed();\
    };\
private:\
    type m_##name {};
	
#define ___AxREADONLY__2(type, name)\
    type ___##name##Writable {};\
	const type& name = ___##name##Writable;
	
#define ___AxREADONLY__3(type, name, default)\
    type ___##name##Writable {default};\
	const type& name = ___##name##Writable;

#define ___AxBINDABLE__4(item, type, name, setter)\
public:\
    Q_PROPERTY(type name READ name WRITE setter BINDABLE m_##name##Bindable)\
public:\
    Q_SIGNAL void name##Changed();\
public:\
    const type& name() const {\
        return m_##name;\
    };\
    void setter(const type& newValue) {\
        if (AxTYPED_EQ_COMPARATOR(type, m_##name, newValue)) return;\
        m_##name = newValue;\
        emit name##Changed();\
    };\
    QBindable<type> m_##name##Bindable() { return QBindable<type>(&m_##name); }\
private:\
    Q_OBJECT_BINDABLE_PROPERTY(item, type, m_##name, &item::name##Changed)

/*****************************************************************************\
 * @brief AxPROPERTY is a Q_PROPERTY alike that generate functions
 *     If used without the setter, the property will be marked CONSTANT
 *     Else, setter functions will be used
 *     So, with two parameters, type and name, ___AxPROPERTY__2 will be called
 *     with three parameters, type, name and setter, ___AxPROPERTY__3.
 * @param type: the type of the variable
 * @param name: the name of the variable
 * @param setter: the name of the setter function you wanna use if you wanna
 *     be able to set the property
\*****************************************************************************/
#define AxPROPERTY(...) OPTIONAL_PARAMETER_ADDRESSER(___AxPROPERTY_, __VA_ARGS__)

/*****************************************************************************\
 * @brief AxREADONLY generate a readonly variable for a class
 *    with two parameters, generate a readonly variable of the given type and
 *        a read / write hidden variable with named ___[NAME]Writable
 *    with three parameters add a custom default value
 * @param type: the type of the variable
 * @param name: the name of the variable
 * @param default: the default value of the variable
\*****************************************************************************/
#define AxREADONLY(...) OPTIONAL_PARAMETER_ADDRESSER(___AxREADONLY_, __VA_ARGS__)

/*****************************************************************************\
 * @brief AxBINDABLE is a bindable Q_PROPERTY functions it require 4
 *     parameters, but more can be inserted for the options
 * @param item: the class name of the container
 * @param type: the type of the variable
 * @param name: the name of the variable
 * @param setter: the name of the setter function you wanna use if you wanna
 *     be able to set the property
\*****************************************************************************/
#define AxBINDABLE(...) OPTIONAL_PARAMETER_ADDRESSER(___AxBINDABLE_, __VA_ARGS__)

/*****************************************************************************\
 * @brief AxBOUND set a binding between the given property and functions
 * @param property: the name given creating the property to bind
 * @param function: the function to bind to the property (a lambda returning a
 *     getter for example)
\*****************************************************************************/
#define AxBOUND(property, function) m_##property##Bindable().setBinding(function);

#endif // QHELPER_H
