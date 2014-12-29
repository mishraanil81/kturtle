/*
	Copyright (C) 2003-2006 Cies Breijs <cies AT kde DOT nl>

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public
	License along with this program; if not, write to the Free
	Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
	Boston, MA 02110-1301, USA.
*/

#include "translator.h"

#include <QDomDocument>
#include <QFile>
#include <QLocale>
#include <QDebug>

#include <KGlobal>

#include "token.h"


Translator* Translator::m_instance = 0;  // initialize pointer

Translator* Translator::instance()
{
	if (m_instance == 0) m_instance = new Translator;  // create sole instance if its the first call
	return m_instance;  // address of sole instance
}

Translator::Translator()
	: localizer(QStringList() << DEFAULT_LANGUAGE_CODE)
{
}

Translator::~Translator()
{
	delete m_instance;
	m_instance = 0;
}


int Translator::look2type(QString& look)
{
	if (look2typeMap.contains(look))
		return look2typeMap[look];
	return Token::Unknown;
}

int Translator::look2type(QChar& look)
{
	if (look2typeMap.contains(static_cast<QString>(look)))
		return look2typeMap[static_cast<QString>(look)];
	return Token::Unknown;
}

QList<QString> Translator::type2look(int type)
{
	return look2typeMap.keys(type);
}

QHash<int, QList<QString> > Translator::token2stringsMap()
{
	QHash<int, QList<QString> > resultMap;
	QList<int> tokenList = look2typeMap.values();
	foreach (int token, tokenList) resultMap.insert(token, look2typeMap.keys(token));
	return resultMap;
}


bool Translator::setLanguage(const QString &lang_code)
{
	// FIXME default to GUI language? return false when language not available?
	localizer = QStringList() << lang_code << DEFAULT_LANGUAGE_CODE;

	setDictionary();
	setExamples();

	return true;
}


void Translator::setDictionary()
{
	look2typeMap.clear();
	default2localizedMap.clear();

	QString localizedCommandLook;


//BEGIN GENERATED translator_cpp CODE

/* The code between the line that start with "//BEGIN GENERATED" and "//END GENERATED"
 * is generated by "generate.rb" according to the definitions specified in
 * "definitions.rb". Please make all changes in the "definitions.rb" file, since all
 * all change you make here will be overwritten the next time "generate.rb" is run.
 * Thanks for looking at the code!
 */

	look2typeMap["$"] = Token::VariablePrefix;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'True' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"true").toString(localizer);
	default2localizedMap["true"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::True;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'False' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"false").toString(localizer);
	default2localizedMap["false"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::False;

	look2typeMap["#"] = Token::Comment;

	look2typeMap["\""] = Token::StringDelimiter;

	look2typeMap["{"] = Token::ScopeOpen;

	look2typeMap["}"] = Token::ScopeClose;

	look2typeMap["("] = Token::ParenthesisOpen;

	look2typeMap[")"] = Token::ParenthesisClose;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'ArgumentSeparator' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		",").toString(localizer);
	default2localizedMap[","] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::ArgumentSeparator;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'DecimalSeparator' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		".").toString(localizer);
	default2localizedMap["."] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::DecimalSeparator;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Exit' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"exit").toString(localizer);
	default2localizedMap["exit"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Exit;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'If' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"if").toString(localizer);
	default2localizedMap["if"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::If;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Else' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"else").toString(localizer);
	default2localizedMap["else"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Else;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Repeat' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"repeat").toString(localizer);
	default2localizedMap["repeat"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Repeat;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'While' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"while").toString(localizer);
	default2localizedMap["while"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::While;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'For' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"for").toString(localizer);
	default2localizedMap["for"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::For;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'To' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"to").toString(localizer);
	default2localizedMap["to"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::To;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Step' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"step").toString(localizer);
	default2localizedMap["step"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Step;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Break' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"break").toString(localizer);
	default2localizedMap["break"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Break;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Return' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"return").toString(localizer);
	default2localizedMap["return"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Return;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Wait' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"wait").toString(localizer);
	default2localizedMap["wait"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Wait;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Assert' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"assert").toString(localizer);
	default2localizedMap["assert"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Assert;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'And' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"and").toString(localizer);
	default2localizedMap["and"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::And;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Or' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"or").toString(localizer);
	default2localizedMap["or"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Or;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Not' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"not").toString(localizer);
	default2localizedMap["not"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Not;

	look2typeMap["=="] = Token::Equals;

	look2typeMap["!="] = Token::NotEquals;

	look2typeMap[">"] = Token::GreaterThan;

	look2typeMap["<"] = Token::LessThan;

	look2typeMap[">="] = Token::GreaterOrEquals;

	look2typeMap["<="] = Token::LessOrEquals;

	look2typeMap["+"] = Token::Addition;

	look2typeMap["-"] = Token::Substracton;

	look2typeMap["*"] = Token::Multiplication;

	look2typeMap["/"] = Token::Division;

	look2typeMap["^"] = Token::Power;

	look2typeMap["="] = Token::Assign;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Learn' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"learn").toString(localizer);
	default2localizedMap["learn"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Learn;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Reset' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"reset").toString(localizer);
	default2localizedMap["reset"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Reset;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Clear' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"clear").toString(localizer);
	default2localizedMap["clear"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Clear;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Clear' COMMAND ALIAS, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"ccl").toString(localizer);
	default2localizedMap["ccl"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Clear;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Center' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"center").toString(localizer);
	default2localizedMap["center"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Center;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Go' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"go").toString(localizer);
	default2localizedMap["go"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Go;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'GoX' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"gox").toString(localizer);
	default2localizedMap["gox"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::GoX;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'GoX' COMMAND ALIAS, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"gx").toString(localizer);
	default2localizedMap["gx"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::GoX;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'GoY' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"goy").toString(localizer);
	default2localizedMap["goy"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::GoY;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'GoY' COMMAND ALIAS, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"gy").toString(localizer);
	default2localizedMap["gy"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::GoY;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Forward' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"forward").toString(localizer);
	default2localizedMap["forward"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Forward;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Forward' COMMAND ALIAS, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"fw").toString(localizer);
	default2localizedMap["fw"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Forward;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Backward' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"backward").toString(localizer);
	default2localizedMap["backward"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Backward;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Backward' COMMAND ALIAS, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"bw").toString(localizer);
	default2localizedMap["bw"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Backward;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Direction' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"direction").toString(localizer);
	default2localizedMap["direction"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Direction;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Direction' COMMAND ALIAS, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"dir").toString(localizer);
	default2localizedMap["dir"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Direction;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'TurnLeft' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"turnleft").toString(localizer);
	default2localizedMap["turnleft"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::TurnLeft;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'TurnLeft' COMMAND ALIAS, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"tl").toString(localizer);
	default2localizedMap["tl"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::TurnLeft;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'TurnRight' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"turnright").toString(localizer);
	default2localizedMap["turnright"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::TurnRight;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'TurnRight' COMMAND ALIAS, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"tr").toString(localizer);
	default2localizedMap["tr"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::TurnRight;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'PenWidth' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"penwidth").toString(localizer);
	default2localizedMap["penwidth"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::PenWidth;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'PenWidth' COMMAND ALIAS, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"pw").toString(localizer);
	default2localizedMap["pw"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::PenWidth;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'PenUp' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"penup").toString(localizer);
	default2localizedMap["penup"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::PenUp;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'PenUp' COMMAND ALIAS, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"pu").toString(localizer);
	default2localizedMap["pu"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::PenUp;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'PenDown' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"pendown").toString(localizer);
	default2localizedMap["pendown"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::PenDown;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'PenDown' COMMAND ALIAS, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"pd").toString(localizer);
	default2localizedMap["pd"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::PenDown;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'PenColor' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"pencolor").toString(localizer);
	default2localizedMap["pencolor"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::PenColor;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'PenColor' COMMAND ALIAS, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"pc").toString(localizer);
	default2localizedMap["pc"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::PenColor;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'CanvasColor' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"canvascolor").toString(localizer);
	default2localizedMap["canvascolor"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::CanvasColor;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'CanvasColor' COMMAND ALIAS, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"cc").toString(localizer);
	default2localizedMap["cc"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::CanvasColor;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'CanvasSize' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"canvassize").toString(localizer);
	default2localizedMap["canvassize"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::CanvasSize;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'CanvasSize' COMMAND ALIAS, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"cs").toString(localizer);
	default2localizedMap["cs"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::CanvasSize;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'SpriteShow' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"spriteshow").toString(localizer);
	default2localizedMap["spriteshow"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::SpriteShow;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'SpriteShow' COMMAND ALIAS, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"ss").toString(localizer);
	default2localizedMap["ss"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::SpriteShow;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'SpriteHide' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"spritehide").toString(localizer);
	default2localizedMap["spritehide"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::SpriteHide;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'SpriteHide' COMMAND ALIAS, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"sh").toString(localizer);
	default2localizedMap["sh"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::SpriteHide;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Print' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"print").toString(localizer);
	default2localizedMap["print"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Print;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'FontSize' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"fontsize").toString(localizer);
	default2localizedMap["fontsize"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::FontSize;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Random' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"random").toString(localizer);
	default2localizedMap["random"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Random;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Random' COMMAND ALIAS, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"rnd").toString(localizer);
	default2localizedMap["rnd"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Random;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'GetX' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"getx").toString(localizer);
	default2localizedMap["getx"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::GetX;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'GetY' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"gety").toString(localizer);
	default2localizedMap["gety"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::GetY;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Message' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"message").toString(localizer);
	default2localizedMap["message"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Message;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Ask' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"ask").toString(localizer);
	default2localizedMap["ask"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Ask;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Pi' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"pi").toString(localizer);
	default2localizedMap["pi"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Pi;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Tan' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"tan").toString(localizer);
	default2localizedMap["tan"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Tan;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Sin' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"sin").toString(localizer);
	default2localizedMap["sin"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Sin;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Cos' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"cos").toString(localizer);
	default2localizedMap["cos"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Cos;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'ArcTan' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"arctan").toString(localizer);
	default2localizedMap["arctan"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::ArcTan;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'ArcSin' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"arcsin").toString(localizer);
	default2localizedMap["arcsin"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::ArcSin;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'ArcCos' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"arccos").toString(localizer);
	default2localizedMap["arccos"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::ArcCos;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Sqrt' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"sqrt").toString(localizer);
	default2localizedMap["sqrt"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Sqrt;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Round' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"round").toString(localizer);
	default2localizedMap["round"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Round;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'GetDirection' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"getdirection").toString(localizer);
	default2localizedMap["getdirection"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::GetDirection;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Mod' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"mod").toString(localizer);
	default2localizedMap["mod"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Mod;


//END GENERATED translator_cpp CODE

}



void Translator::setExamples()
{
	examples.clear();
	QString exampleName;

	exampleName = ki18nc(
		"This is an EXAMPLE NAME in KTurtle."
		"Please see http://edu.kde.org/kturtle/translator.php to learn know how to properly translate it.",
		"triangle").toString(localizer);
	examples[exampleName] = localizeScript(QString(
				"@(reset)\n"
				"@(repeat) 3 {\n"
				"  @(forward) 100\n"
				"  @(turnleft) 120\n"
				"}\n"
		));

	exampleName = ki18nc(
		"This is an EXAMPLE NAME in KTurtle."
		"Please see http://edu.kde.org/kturtle/translator.php to learn know how to properly translate it.",
		"curly").toString(localizer);
	examples[exampleName] = localizeScript(QString(
				"@(reset)\n"
				"@(penup)\n"
				"@(forward) 50\n"
				"@(pendown)\n"
				"\n"
				"@(repeat) 4 {\n"
				"  @(for) $x = 1 @(to) 100 {\n"
				"    @(forward) 10\n"
				"    @(turnright) 100 - $x\n"
				"  }\n"
				"}\n"
		));

	exampleName = ki18nc(
		"This is an EXAMPLE NAME in KTurtle."
		"Please see http://edu.kde.org/kturtle/translator.php to learn know how to properly translate it.",
		"arrow").toString(localizer);
	examples[exampleName] = localizeScript(QString(
				"@(reset)\n"
				"\n"
				"@(canvassize) 200@(,) 200\n"
				"@(canvascolor) 0@(,) 0@(,) 0\n"
				"@(pencolor) 255@(,) 0@(,) 0\n"
				"@(penwidth) 5\n"
				"\n"
				"@(go) 20@(,)20\n"
				"@(direction) 135\n"
				"\n"
				"@(forward) 200\n"
				"@(turnleft) 135\n"
				"@(forward) 100\n"
				"@(turnleft) 135\n"
				"@(forward) 141\n"
				"@(turnleft) 135\n"
				"@(forward) 100\n"
				"@(turnleft) 45\n"
				"\n"
				"@(go) 40@(,) 100"
		));

	exampleName = ki18nc(
		"This is an EXAMPLE NAME in KTurtle."
		"Please see http://edu.kde.org/kturtle/translator.php to learn know how to properly translate it.",
		  "flower").toString(localizer);
	examples[exampleName] = localizeScript(QString(
				"@(reset)\n"
				"@(canvascolor) 255@(,) 55@(,) 140\n"
				"@(pencolor) 160@(,) 0@(,) 255\n"
				"@(penwidth) 3\n"
				"\n"
				"@(repeat) 8 {\n"
				"  @(repeat) 4 {\n"
				"    @(forward) 20\n"
				"    @(turnright) 30\n"
				"  }\n"
				"  @(repeat) 7 {\n"
				"    @(forward) 10\n"
				"    @(turnright) 15\n"
				"  }\n"
				"  @(repeat) 9 {\n"
				"    @(forward) 3\n"
				"    @(turnright) 10\n"
				"  }\n"
				"}\n"
				"\n"
				"@(go) 145@(,) 145\n"
				"@(direction) 0"
		));

}

QString Translator::localizeScript(const QString& untranslatedScript)
{
	QString result = untranslatedScript;
	Translator* translator = Translator::instance();
	QRegExp rx("@\\(.*\\)");
	rx.setMinimal(true);  // make it not greedy

	int pos = 0;
	while ((pos = rx.indexIn(result, pos)) != -1) {
		QString original = result.mid(pos, rx.matchedLength());
		original = original.mid(2, original.length() - 3);
		result = result.replace(pos, rx.matchedLength(), translator->default2localized(original));
	}

	return result;
}
