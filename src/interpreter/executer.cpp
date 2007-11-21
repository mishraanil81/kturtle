/*
	Copyright (C) 2003-2006 Cies Breijs <cies AT kde DOT nl>

	This program is free software; you can redistribute it and/or
	modify it under the terms of version 2 of the GNU General Public
	License as published by the Free Software Foundation.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public
	License along with this program; if not, write to the Free
	Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
	Boston, MA 02110-1301, USA.
*/


// This file is originally written by Walter Scheppers, but almost
// every aspect of it is slightly changed by Cies Breijs.

#include "executer.h"

#include <iostream>
#include <math.h>
#include <unistd.h>  // for usleep();

#include <QTimer>  // for wait

#include <QtDebug>

#include <klocale.h>
#include <krandom.h>

#include <kdebug.h>

// this function is used in executer and canvas:
#define ROUND2INT(x) ( (x) >= 0 ? (int)( (x) + .5 ) : (int)( (x) - .5 ) )

#define DEG2RAD(deg) ( deg * (M_PI / 180) )
#define RAD2DEG(rad) ( rad * (180 / M_PI) )

void Executer::initialize(TreeNode* tree, ErrorList* _errorList)
{
	rootNode       = tree;
	newScope       = rootNode;
	currentNode    = rootNode;
	finished       = !currentNode->hasChildren();  // set finished to false unless the tree is empty
	errorList      = _errorList;

	breaking       = false;
	returning      = false;
	waiting        = false;
	returnValue    = 0;
	
	executeCurrent = false;

	functionTable.clear();
	globalVariableTable.clear();

	while (!functionStack.isEmpty()) delete functionStack.pop().variableTable;
}


void Executer::execute()
{
	if (finished || waiting) return;
// 	qDebug() << "Executer::execute() -- main execute loop called";

	if (executeCurrent) {
		// executeCurrent is used to make sure the currentNode will be executed
		// this way the tree will not be walked before the execution...
// 		qDebug() << ">> jumping to tree node, and executing: " << currentNode->token()->look();
		executeCurrent = false;
		execute(currentNode);
		return;
	} else if (returning) {
		delete functionStack.top().variableTable;
		currentNode = functionStack.pop().function;
// 		qDebug() << ">> returning to: " << currentNode->token()->look();

		if (returnValue == 0) currentNode->setNullValue();  // Handle an empty return value
		else currentNode->setValue(returnValue);
// // // 		returnValue = 0;  // DONT DO THIS... the the functionCall node that get recalled now handle it...
// // // 		returning   = false;

		execute(currentNode);
		return;
	} else {
		if (newScope == 0) {  // same scope
// 			qDebug() << ">> to next sibling";
			
			TreeNode* currentParent = currentNode->parent();
			currentNode = currentNode->nextSibling();
		
			if (currentNode == 0) {  // running off sibling list
// 				qDebug() << ">> to parent";
				currentNode = currentParent;
				if (currentNode == rootNode) {
// 					qDebug() << ">> hit root";
					finished = true;
					return;
				}

				// don't report scopes (their are not really executed)
				if (currentNode->token()->type() != Token::Scope)
					std::cout << "EXE> " << qPrintable(currentNode->token()->look()) << std::endl;
				execute(currentNode);
				return;
			}
		} else {  // entering new scope
// 			qDebug() << ">> to the new scope";
			currentNode = newScope;
			newScope = 0;
			
			// skip ahead to frist child (if any) else we will not get into the scope
			if (currentNode->hasChildren()) currentNode = currentNode->firstChild();
		}
	}
	
// 	qDebug() << ">> to top";
	while (currentNode->hasChildren() && currentNode->token()->type() != Token::Scope) {
//Niels: I don't know why, but the following lines break learn
//		if (currentNode->token()->type() == Token::Learn) {
//			currentNode = currentNode->nextSibling();
//			if (currentNode == 0) {
//				finished = true;
//				return;
//			}
//		}
		currentNode = currentNode->firstChild();
	}

	// don't report scopes (their are not really executed)
	if (currentNode->token()->type() != Token::Scope)
		std::cout << "EXE> " << qPrintable(currentNode->token()->look()) << std::endl;

	execute(currentNode);
}


void Executer::execute(TreeNode* node)
{
	if (finished) return;

	// emit a signal for GUI
	Token* t = node->token();
// 	kDebug(0) << "emitting token: '" << t->look() << "' - (" << t->startRow() << "," << t->startCol() << " - " << t->endRow() << "," << t->endCol() << ")";

	// don't report scopes (their are not really executed)
	if (t->type() != Token::Scope)
		emit currentlyExecuting(t->startRow(), t->startCol(), t->endRow(), t->endCol());

	// this method executes one node at the time

	// if (currentNode->token()->type() != Token::Scope) qDebug() << "1234567890!!!!!";

	switch (node->token()->type()) {

//BEGIN GENERATED executer_switch_cpp CODE

/* The code between the line that start with "//BEGIN GENERATED" and "//END GENERATED"
 * is generated by "generate.rb" according to the definitions specified in
 * "definitions.rb". Please make all changes in the "definitions.rb" file, since all
 * all change you make here will be overwritten the next time "generate.rb" is run.
 * Thanks for looking at the code!
 */

		case Token::Unknown             : executeUnknown(node);             break;
		case Token::Root                : executeRoot(node);                break;
		case Token::Scope               : executeScope(node);               break;
		case Token::Variable            : executeVariable(node);            break;
		case Token::FunctionCall        : executeFunctionCall(node);        break;
		case Token::String              : /* a constant; do nothing */      break;
		case Token::Number              : /* a constant; do nothing */      break;
		case Token::True                : /* a constant; do nothing */      break;
		case Token::False               : /* a constant; do nothing */      break;
		case Token::Exit                : executeExit(node);                break;
		case Token::If                  : executeIf(node);                  break;
		case Token::Else                : executeElse(node);                break;
		case Token::Repeat              : executeRepeat(node);              break;
		case Token::While               : executeWhile(node);               break;
		case Token::For                 : executeFor(node);                 break;
		case Token::ForTo               : executeForTo(node);               break;
		case Token::Break               : executeBreak(node);               break;
		case Token::Return              : executeReturn(node);              break;
		case Token::Wait                : executeWait(node);                break;
		case Token::And                 : executeAnd(node);                 break;
		case Token::Or                  : executeOr(node);                  break;
		case Token::Not                 : executeNot(node);                 break;
		case Token::Equals              : executeEquals(node);              break;
		case Token::NotEquals           : executeNotEquals(node);           break;
		case Token::GreaterThan         : executeGreaterThan(node);         break;
		case Token::LessThan            : executeLessThan(node);            break;
		case Token::GreaterOrEquals     : executeGreaterOrEquals(node);     break;
		case Token::LessOrEquals        : executeLessOrEquals(node);        break;
		case Token::Addition            : executeAddition(node);            break;
		case Token::Substracton         : executeSubstracton(node);         break;
		case Token::Multiplication      : executeMultiplication(node);      break;
		case Token::Division            : executeDivision(node);            break;
		case Token::Power               : executePower(node);               break;
		case Token::Assign              : executeAssign(node);              break;
		case Token::Learn               : executeLearn(node);               break;
		case Token::ArgumentList        : executeArgumentList(node);        break;
		case Token::Reset               : executeReset(node);               break;
		case Token::Clear               : executeClear(node);               break;
		case Token::Center              : executeCenter(node);              break;
		case Token::Go                  : executeGo(node);                  break;
		case Token::GoX                 : executeGoX(node);                 break;
		case Token::GoY                 : executeGoY(node);                 break;
		case Token::Forward             : executeForward(node);             break;
		case Token::Backward            : executeBackward(node);            break;
		case Token::Direction           : executeDirection(node);           break;
		case Token::TurnLeft            : executeTurnLeft(node);            break;
		case Token::TurnRight           : executeTurnRight(node);           break;
		case Token::PenWidth            : executePenWidth(node);            break;
		case Token::PenUp               : executePenUp(node);               break;
		case Token::PenDown             : executePenDown(node);             break;
		case Token::PenColor            : executePenColor(node);            break;
		case Token::CanvasColor         : executeCanvasColor(node);         break;
		case Token::SpriteShow          : executeSpriteShow(node);          break;
		case Token::SpriteHide          : executeSpriteHide(node);          break;
		case Token::Print               : executePrint(node);               break;
		case Token::FontSize            : executeFontSize(node);            break;
		case Token::Random              : executeRandom(node);              break;
		case Token::GetX                : executeGetX(node);                break;
		case Token::GetY                : executeGetY(node);                break;
		case Token::Message             : executeMessage(node);             break;
		case Token::Ask                 : executeAsk(node);                 break;
		case Token::Pi                  : executePi(node);                  break;
		case Token::Tan                 : executeTan(node);                 break;
		case Token::Sin                 : executeSin(node);                 break;
		case Token::Cos                 : executeCos(node);                 break;
		case Token::ArcTan              : executeArcTan(node);              break;
		case Token::ArcSin              : executeArcSin(node);              break;
		case Token::ArcCos              : executeArcCos(node);              break;
		case Token::Sqrt                : executeSqrt(node);                break;
		case Token::Exp                 : executeExp(node);                 break;

//END GENERATED executer_switch_cpp CODE

		default:
			qDebug() << "No method to execute this tree node, THIS SHOULDN'T HAPPEN!";
			std::cout << "EXE> " << "No method to execute this tree node, THIS SHOULDN'T HAPPEN!" << std::endl;
			break;

	}

}


VariableTable* Executer::currentVariableTable()
{
	if (functionStack.isEmpty())
		return &globalVariableTable;
	else
		return functionStack.top().variableTable;
}




bool Executer::checkParameterQuantity(TreeNode* node, uint quantity, int errorCode)
{
// 	qDebug() << "Executer::checkParameterQuantity";
	uint nodeSize = node->childCount();

	if (quantity == 0) {
		if (nodeSize == 0) return true;  // thats easy!
		i18n("Internationalized string with an %1", QString("argument"));
		addError(i18n("The %1 command accepts no parameters.", node->token()->look()), *node->token(), errorCode);
		return false;
	}
	
// 	// CHECK THIS OUT LATER
// 	if (nodeSize != 0) // when all parameters are forgotten the parser puts a Unknown/tokEOL param, catch this:
// 		if (node->firstChild()->getToken().type == tokEOL) nodeSize = 0;
	
	if (nodeSize != quantity) {
		if (nodeSize < quantity) {
			addError(i18n("The %1 command was called with %2 but needs 1 parameter.", node->token()->look(), nodeSize), *node->token(), errorCode);
		} else {
			addError(i18n("The %1 command was called with %2 but only accepts 1 parameter.", node->token()->look(), nodeSize), *node->token(), errorCode);
		}
		return false;
	}
	return true; // if all tests passed
}


bool Executer::checkParameterType(TreeNode* node, int valueType, int errorCode)
{
// 	qDebug() << "Executer::checkParameterType";
	uint quantity = node->childCount();
	TreeNode* currentChild = node->firstChild();
	while (currentChild != 0) {
		if (currentChild->value()->type() != valueType) {
			switch (valueType) {
				case Value::String:
					if (quantity == 1)
						addError(i18n("The %1 command only accepts a string as its parameter.", node->token()->look()), *node->token(), errorCode);
					else
						addError(i18n("The %1 command only accepts strings as its parameters.", node->token()->look()), *node->token(), errorCode);
					break;
				
				case Value::Number:
					if (quantity == 1)
						addError(i18n("The %1 command only accepts a number as its parameter.", node->token()->look()), *node->token(), errorCode);
					else
						addError(i18n("The %1 command only accepts numbers as its parameters.", node->token()->look()), *node->token(), errorCode);
					break;
				
				case Value::Bool:
					if (quantity == 1)
						addError(i18n("The %1 command only accepts an answer as its parameter.", node->token()->look()), *node->token(), errorCode);
					else
						addError(i18n("The %1 command only accepts answers as its parameters.", node->token()->look()), *node->token(), errorCode);
					break;
			}
			
			return false;
		}

		currentChild = node->nextChild();
	}
	return true; // if all tests passed
}


void Executer::addError(const QString& s, const Token& t, int code)
{
	if (m_testing)
		std::cout << "ERR> " << qPrintable(s) << " (runtime error)" << std::endl;
	else
		errorList->addError(s, t, code);
}



//BEGIN GENERATED executer_cpp CODE

/* The code between the line that start with "//BEGIN GENERATED" and "//END GENERATED"
 * is generated by "generate.rb" according to the definitions specified in
 * "definitions.rb". Please make all changes in the "definitions.rb" file, since all
 * all change you make here will be overwritten the next time "generate.rb" is run.
 * Thanks for looking at the code!
 */

void Executer::executeUnknown(TreeNode* node) {
//	qDebug() << "Executer::executeUnknown()";
	if (node->parent()->token()->type() == Token::Learn) {
		currentNode = node->parent();
		executeCurrent = true;
		return;
	}
}
void Executer::executeRoot(TreeNode* node) {
//	qDebug() << "Executer::executeRoot()";
	node = node; // stop the warnings // this is a stud
}
void Executer::executeScope(TreeNode* node) {
//	qDebug() << "Executer::executeScope()";
	// catch loops, they need to be managed...
	int parentTokenType = node->parent()->token()->type();
	if (parentTokenType == Token::If     ||
	    parentTokenType == Token::Repeat ||
	    parentTokenType == Token::While  ||
//	    parentTokenType == Token::ForIn  ||
	    parentTokenType == Token::ForTo) {
		currentNode = node->parent();
		executeCurrent = true;
		return;
	}
	if(parentTokenType == Token::Learn) {
		//We have the end of a Learn, so we should return
		returning = true;
		returnValue = 0;
		return;
	}
	newScope = node;
}
void Executer::executeVariable(TreeNode* node) {
//	qDebug() << "Executer::executeVariable()";
	// no need to look up when assigning (in a for loop statement)
	if (node->parent()->token()->type() == Token::Assign ||
	    node->parent()->token()->type() == Token::ForTo)
		return;

	if (!functionStack.isEmpty() && 
	    functionStack.top().variableTable->contains(node->token()->look())) {
		qDebug() << "exists locally";
		node->setValue( (*functionStack.top().variableTable)[node->token()->look()] );
	} else if (globalVariableTable.contains(node->token()->look())) {
		qDebug() << "exists globally";
		node->setValue(globalVariableTable[node->token()->look()]);
	} else {
		addError(i18n("The variable '%1' was used without first being assigned to a value", node->token()->look()), *node->token(), 0);
	}
}
void Executer::executeFunctionCall(TreeNode* node) {
//	qDebug() << "Executer::executeFunctionCall()";
	if (returning) {  // if the function is already executed and returns now
		returnValue = 0;
		returning = false;
		qDebug() << "==> functionReturned!";
		return;
	}

	if (!functionTable.contains(node->token()->look())) {
		addError(i18n("An unknown function named '%1' was called", node->token()->look()), *node->token(), 0);
		return;
	}
	
	CalledFunction c;
	c.function      = node;
	c.variableTable = new VariableTable();
	functionStack.push(c);
	qDebug() << "==> functionCalled!";
	
	TreeNode* learnNode = functionTable[node->token()->look()];

	// if the parameter numbers are not equal...
	if (node->childCount() != learnNode->child(1)->childCount()) {
		addError(
			i18n("The function '%1' was called with %2, while it should be called with %3",
				node->token()->look(),
				i18np("1 parameter", "%1 parameters", node->childCount()),
				i18np("1 parameter", "%1 parameters", learnNode->child(1)->childCount())
			),
			*node->token(), 0);
		return;
	}
		
	for (uint i = 0; i < node->childCount(); i++) {
		functionStack.top().variableTable->insert(learnNode->child(1)->child(i)->token()->look(), node->child(i)->value());
		qDebug() << "inserted variable " << learnNode->child(1)->child(i)->token()->look() << " on function stack";
	}
	newScope = learnNode->child(2);
}
void Executer::executeExit(TreeNode* node) {
//	qDebug() << "Executer::executeExit()";
	node = node; // stop the warnings
	finished = true;
}
void Executer::executeIf(TreeNode* node) {
//	qDebug() << "Executer::executeIf()";
	QString id = QString("__%1_%2").arg(node->token()->look()).arg((long)node);
	if (currentVariableTable()->contains(id)) {
		currentVariableTable()->remove(id);
		return;
	}
	currentVariableTable()->insert(id, Value()); // store a empty Value just to know we executed once
	if (node->child(0)->value()->boolean()) {
		newScope = node->child(1);
	} else {
		if (node->childCount() >= 3)
			newScope = node->child(2); // execute the else part
	}
}
void Executer::executeElse(TreeNode* node) {
//	qDebug() << "Executer::executeElse()";
	execute(node->child(0));  // execute the scope, that's all...
}
void Executer::executeRepeat(TreeNode* node) {
//	qDebug() << "Executer::executeRepeat()";
	breaking = false;
	QString id = QString("__%1_%2").arg(node->token()->look()).arg((long)node);
	// the iteration state is stored on the variable table
	if (currentVariableTable()->contains(id)) {
		int currentCount = ROUND2INT((*currentVariableTable())[id].number());
		if (currentCount > 0) {
			(*currentVariableTable())[id].setNumber(currentCount - 1);
		} else {
			currentVariableTable()->remove(id);
			return;
		}
	} else {
		currentVariableTable()->insert(id, Value((double)(ROUND2INT(node->child(0)->value()->number()) - 1)));
	}
	newScope = node->child(1);
}
void Executer::executeWhile(TreeNode* node) {
//	qDebug() << "Executer::executeWhile()";
	// first time this gets called the expression is already executed
	// after one iteration the expression is not automatically re-executed.
	// so we do the following on every call to executeWhile:
	//     exec scope, exec expression, exec scope, exec expression, ...

	QString id = QString("__%1_%2").arg(node->token()->look()).arg((long)node);
	if (currentVariableTable()->contains(id)) {
		newScope = node; // re-execute the expression
		currentVariableTable()->remove(id);
		return;
	}
	currentVariableTable()->insert(id, Value()); // store a empty Value just to know we executed once

	if (node->child(0)->value()->boolean())
		newScope = node->child(1); // (re-)execute the scope
	else
		currentVariableTable()->remove(id); // clean-up, keep currenNode on currentNode so the next sibling we be run next
}
void Executer::executeFor(TreeNode* node) {
//	qDebug() << "Executer::executeFor()";
	qCritical("Executer::executeFor(): should have been translated to Token::ForTo by the parser");
	node = node; // stop the warnings
}
void Executer::executeForTo(TreeNode* node) {
//	qDebug() << "Executer::executeForTo()";
	// first time this gets called the expressions are already executed
	// after one iteration the expression is not re-executed.
	// so we do: exec scope, exec expressions, exec scope, exec expressions, ...

	bool firstIteration = false;
	if (functionStack.isEmpty() || functionStack.top().function != node) {
		// if this for loop is called for the first time...
		CalledFunction c;
		c.function      = node;
		c.variableTable = new VariableTable();
		functionStack.push(c);

		currentVariableTable()->insert(node->child(0)->token()->look(), Value(node->child(1)->value()->number()));
		firstIteration = true;
	}

	QString id = QString("__%1_%2").arg(node->token()->look()).arg((long)node);

	if (currentVariableTable()->contains(id)) {
		newScope = node; // re-execute the expressions
		currentVariableTable()->remove(id);
		return;
	}
	currentVariableTable()->insert(id, Value()); // store a empty Value just to know we executed once

	double currentCount   = (*currentVariableTable())[node->child(0)->token()->look()].number();
	double startCondition = node->child(1)->value()->number();
	double endCondition   = node->child(2)->value()->number();
	double step           = node->child(3)->value()->number();

	if ((startCondition < endCondition && currentCount + step < endCondition) ||
	    (startCondition > endCondition && currentCount + step > endCondition)) {
		if (!firstIteration)
			(*currentVariableTable())[node->child(0)->token()->look()].setNumber(currentCount + step);
		newScope = node->child(4); // (re-)execute the scope
	} else {
		// cleaning up after last iteration...
		delete functionStack.top().variableTable;
		functionStack.pop();
	}
}
void Executer::executeBreak(TreeNode* node) {
//	qDebug() << "Executer::executeBreak()";
	if (!checkParameterQuantity(node, 0, 20000+Token::Break*100+90)) return;
}
void Executer::executeReturn(TreeNode* node) {
//	qDebug() << "Executer::executeReturn()";
	if(node->childCount()>0)
		returnValue = node->child(0)->value();
	else
		returnValue = 0;
	returning   = true;
}
void Executer::executeWait(TreeNode* node) {
//	qDebug() << "Executer::executeWait()";
	if (!checkParameterQuantity(node, 1, 20000+Token::Wait*100+90)) return;
	if (!checkParameterType(node, Value::Number, 20000+Token::Wait*100+91) ) return;
	waiting = true;
	QTimer::singleShot((int)(1000*node->child(0)->value()->number()), this, SLOT(stopWaiting()));
}
void Executer::executeAnd(TreeNode* node) {
//	qDebug() << "Executer::executeAnd()";
	//Niels: See 'Not'
	if(node->childCount()!=2) {
		addError(i18n("'And' needs two variables"), *node->token(), 0);
		return;
	}
	node->value()->setBool(node->child(0)->value()->boolean() && node->child(1)->value()->boolean());
}
void Executer::executeOr(TreeNode* node) {
//	qDebug() << "Executer::executeOr()";
	//Niels: See 'Not'
	if(node->childCount()!=2) {
		addError(i18n("'Or' needs two variables"), *node->token(), 0);
		return;
	}
	node->value()->setBool(node->child(0)->value()->boolean() || node->child(1)->value()->boolean());
}
void Executer::executeNot(TreeNode* node) {
//	qDebug() << "Executer::executeNot()";
	// OLD-TODO: maybe add some error handling here...
	//Niels: Ok, now we check if the node has children. Should we also check whether the child value is a boolean?
	if(node->childCount()!=1) {
		addError(i18n("I need something to do a not on"), *node->token(), 0);
		return;
	}
	node->value()->setBool(!node->child(0)->value()->boolean());
}
void Executer::executeEquals(TreeNode* node) {
//	qDebug() << "Executer::executeEquals()";
	if(node->childCount()!=2) { 
		addError(i18n("I cannot do a '==' without 2 variables"), *node->token(), 0);
		return;
	}
	node->value()->setBool(*node->child(0)->value() == node->child(1)->value());
}
void Executer::executeNotEquals(TreeNode* node) {
//	qDebug() << "Executer::executeNotEquals()";
	if(node->childCount()!=2) { 
		addError(i18n("I cannot do a '!=' without 2 variables"), *node->token(), 0);
		return;
	}
	node->value()->setBool(*node->child(0)->value() != node->child(1)->value());
}
void Executer::executeGreaterThan(TreeNode* node) {
//	qDebug() << "Executer::executeGreaterThan()";
	if(node->childCount()!=2) { 
		addError(i18n("I cannot do a '>' without 2 variables"), *node->token(), 0);
		return;
	}
	node->value()->setBool(*node->child(0)->value() > node->child(1)->value());
}
void Executer::executeLessThan(TreeNode* node) {
//	qDebug() << "Executer::executeLessThan()";
	if(node->childCount()!=2) { 
		addError(i18n("I cannot do a '<' without 2 variables"), *node->token(), 0);
		return;
	}
	node->value()->setBool(*node->child(0)->value() < node->child(1)->value());
}
void Executer::executeGreaterOrEquals(TreeNode* node) {
//	qDebug() << "Executer::executeGreaterOrEquals()";
	if(node->childCount()!=2) { 
		addError(i18n("I cannot do a '>=' without 2 variables"), *node->token(), 0);
		return;
	}
	node->value()->setBool(*node->child(0)->value() >= node->child(1)->value());
}
void Executer::executeLessOrEquals(TreeNode* node) {
//	qDebug() << "Executer::executeLessOrEquals()";
	if(node->childCount()!=2) { 
		addError(i18n("I cannot do a '<=' without 2 variables"), *node->token(), 0);
		return;
	}
	node->value()->setBool(*node->child(0)->value() <= node->child(1)->value());
}
void Executer::executeAddition(TreeNode* node) {
//	qDebug() << "Executer::executeAddition()";
	if(node->childCount()!=2) {
		addError(i18n("You need two numbers or string to do an addition"), *node->token(), 0);
		return;
	}
	if (node->child(0)->value()->type() == Value::Number && node->child(1)->value()->type() == Value::Number) {
		node->value()->setNumber(node->child(0)->value()->number() + node->child(1)->value()->number());
	} else {
		node->value()->setString(node->child(0)->value()->string().append(node->child(1)->value()->string()));
	}
}
void Executer::executeSubstracton(TreeNode* node) {
//	qDebug() << "Executer::executeSubstracton()";
	if(node->childCount()!=2) {
		addError(i18n("You need two numbers to substract"), *node->token(), 0);
		return;
	}
	if (node->child(0)->value()->type() == Value::Number && node->child(1)->value()->type() == Value::Number) {
		node->value()->setNumber(node->child(0)->value()->number() - node->child(1)->value()->number());
	} else {
		if (node->child(0)->value()->type() != Value::Number)
			addError(i18n("You tried to substract from a non-number, '%1'", node->child(0)->token()->look()), *node->token(), 0);
		if (node->child(1)->value()->type() != Value::Number)
			addError(i18n("You tried to substract a non-number, '%1'", node->child(1)->token()->look()), *node->token(), 0);
	}
}
void Executer::executeMultiplication(TreeNode* node) {
//	qDebug() << "Executer::executeMultiplication()";
	if(node->childCount()!=2) {
		addError(i18n("You need two numbers to multiplicate"), *node->token(), 0);
		return;
	}
	if (node->child(0)->value()->type() == Value::Number && node->child(1)->value()->type() == Value::Number) {
		node->value()->setNumber(node->child(0)->value()->number() * node->child(1)->value()->number());
	} else {
		if (node->child(0)->value()->type() != Value::Number)
			addError(i18n("You tried to multiplicate a non-number, '%1'", node->child(0)->token()->look()), *node->token(), 0);
		if (node->child(1)->value()->type() != Value::Number)
			addError(i18n("You tried to multiplicate by a non-number, '%1'", node->child(1)->token()->look()), *node->token(), 0);
	}
}
void Executer::executeDivision(TreeNode* node) {
//	qDebug() << "Executer::executeDivision()";
	if(node->childCount()!=2) {
		addError(i18n("You need two numbers to divide"), *node->token(), 0);
		return;
	}
	if (node->child(0)->value()->type() == Value::Number && node->child(1)->value()->type() == Value::Number) {
		node->value()->setNumber(node->child(0)->value()->number() / node->child(1)->value()->number());
	} else {
		if (node->child(0)->value()->type() != Value::Number)
			addError(i18n("You tried to divide a non-number, '%1'", node->child(0)->token()->look()), *node->token(), 0);
		if (node->child(1)->value()->type() != Value::Number)
			addError(i18n("You tried to divide by a non-number, '%1'", node->child(1)->token()->look()), *node->token(), 0);
	}
}
void Executer::executePower(TreeNode* node) {
//	qDebug() << "Executer::executePower()";
	if(node->childCount()!=2) {
		addError(i18n("You need two numbers to raise a power"), *node->token(), 0);
		return;
	}
	if (node->child(0)->value()->type() == Value::Number && node->child(1)->value()->type() == Value::Number) {
		node->value()->setNumber(pow(node->child(0)->value()->number(), node->child(1)->value()->number()));
	} else {
		if (node->child(0)->value()->type() != Value::Number)
			addError(i18n("You tried to raise a non-number to a power, '%1'", node->child(0)->token()->look()), *node->token(), 0);
		if (node->child(1)->value()->type() != Value::Number)
			addError(i18n("You tried to raise the power of a non-number, '%1'", node->child(1)->token()->look()), *node->token(), 0);
	}
}
void Executer::executeAssign(TreeNode* node) {
//	qDebug() << "Executer::executeAssign()";
	if(node->childCount()!=2) {
	addError(i18n("You need one variable and a value or variable to do a '='"), *node->token(), 0);
		return;
	}
	if (!functionStack.isEmpty()) // &&functionStack.top().variableTable->contains(node->token()->look())) 
	{
	qDebug() << "function scope";
		functionStack.top().variableTable->insert(node->child(0)->token()->look(), node->child(1)->value());
	} else {
	// inserts unless already exists then replaces
	globalVariableTable.insert(node->child(0)->token()->look(), node->child(1)->value());
	}
	qDebug() << "variableTable updated!";
	emit variableTableUpdated(node->child(0)->token()->look(), node->child(1)->value());
}
void Executer::executeLearn(TreeNode* node) {
//	qDebug() << "Executer::executeLearn()";
	if(functionTable.contains(node->child(0)->token()->look())) {
		addError(i18n("The function '%1' is already defined!", node->child(0)->token()->look()), *node->token(), 0);
		return;
	}
	functionTable.insert(node->child(0)->token()->look(), node);
	qDebug() << "functionTable updated!";
	QStringList parameters;
	for (uint i = 0; i < node->child(1)->childCount(); i++)
		parameters << node->child(1)->child(i)->token()->look();
	emit functionTableUpdated(node->child(0)->token()->look(), parameters);
}
void Executer::executeArgumentList(TreeNode* node) {
//	qDebug() << "Executer::executeArgumentList()";
	node = node; // stop the warnings // this is a stud
}
void Executer::executeReset(TreeNode* node) {
//	qDebug() << "Executer::executeReset()";
	if (!checkParameterQuantity(node, 0, 20000+Token::Reset*100+90)) return;
	emit reset();
}
void Executer::executeClear(TreeNode* node) {
//	qDebug() << "Executer::executeClear()";
	if (!checkParameterQuantity(node, 0, 20000+Token::Clear*100+90)) return;
	emit clear();
}
void Executer::executeCenter(TreeNode* node) {
//	qDebug() << "Executer::executeCenter()";
	if (!checkParameterQuantity(node, 0, 20000+Token::Center*100+90)) return;
	emit center();
}
void Executer::executeGo(TreeNode* node) {
//	qDebug() << "Executer::executeGo()";
	if (!checkParameterQuantity(node, 2, 20000+Token::Go*100+90) ||
		!checkParameterType(node, Value::Number, 20000+Token::Go*100+91)) return;
	emit go(node->child(0)->value()->number(), node->child(1)->value()->number());
}
void Executer::executeGoX(TreeNode* node) {
//	qDebug() << "Executer::executeGoX()";
	if (!checkParameterQuantity(node, 1, 20000+Token::GoX*100+90) ||
		!checkParameterType(node, Value::Number, 20000+Token::GoX*100+91)) return;
	emit goX(node->child(0)->value()->number());
}
void Executer::executeGoY(TreeNode* node) {
//	qDebug() << "Executer::executeGoY()";
	if (!checkParameterQuantity(node, 1, 20000+Token::GoY*100+90) ||
		!checkParameterType(node, Value::Number, 20000+Token::GoY*100+91)) return;
	emit goY(node->child(0)->value()->number());
}
void Executer::executeForward(TreeNode* node) {
//	qDebug() << "Executer::executeForward()";
	if (!checkParameterQuantity(node, 1, 20000+Token::Forward*100+90) ||
		!checkParameterType(node, Value::Number, 20000+Token::Forward*100+91)) return;
	emit forward(node->child(0)->value()->number());
}
void Executer::executeBackward(TreeNode* node) {
//	qDebug() << "Executer::executeBackward()";
	if (!checkParameterQuantity(node, 1, 20000+Token::Backward*100+90) ||
		!checkParameterType(node, Value::Number, 20000+Token::Backward*100+91)) return;
	emit backward(node->child(0)->value()->number());
}
void Executer::executeDirection(TreeNode* node) {
//	qDebug() << "Executer::executeDirection()";
	if (!checkParameterQuantity(node, 1, 20000+Token::Direction*100+90) ||
		!checkParameterType(node, Value::Number, 20000+Token::Direction*100+91)) return;
	emit direction(node->child(0)->value()->number());
}
void Executer::executeTurnLeft(TreeNode* node) {
//	qDebug() << "Executer::executeTurnLeft()";
	if (!checkParameterQuantity(node, 1, 20000+Token::TurnLeft*100+90) ||
		!checkParameterType(node, Value::Number, 20000+Token::TurnLeft*100+91)) return;
	emit turnLeft(node->child(0)->value()->number());
}
void Executer::executeTurnRight(TreeNode* node) {
//	qDebug() << "Executer::executeTurnRight()";
	if (!checkParameterQuantity(node, 1, 20000+Token::TurnRight*100+90) ||
		!checkParameterType(node, Value::Number, 20000+Token::TurnRight*100+91)) return;
	emit turnRight(node->child(0)->value()->number());
}
void Executer::executePenWidth(TreeNode* node) {
//	qDebug() << "Executer::executePenWidth()";
	if (!checkParameterQuantity(node, 1, 20000+Token::PenWidth*100+90) ||
		!checkParameterType(node, Value::Number, 20000+Token::PenWidth*100+91)) return;
	emit penWidth(node->child(0)->value()->number());
}
void Executer::executePenUp(TreeNode* node) {
//	qDebug() << "Executer::executePenUp()";
	if (!checkParameterQuantity(node, 0, 20000+Token::PenUp*100+90)) return;
	emit penUp();
}
void Executer::executePenDown(TreeNode* node) {
//	qDebug() << "Executer::executePenDown()";
	if (!checkParameterQuantity(node, 0, 20000+Token::PenDown*100+90)) return;
	emit penDown();
}
void Executer::executePenColor(TreeNode* node) {
//	qDebug() << "Executer::executePenColor()";
	if (!checkParameterQuantity(node, 3, 20000+Token::PenColor*100+90) ||
		!checkParameterType(node, Value::Number, 20000+Token::PenColor*100+91)) return;
	emit penColor(node->child(0)->value()->number(), node->child(1)->value()->number(), node->child(2)->value()->number());
}
void Executer::executeCanvasColor(TreeNode* node) {
//	qDebug() << "Executer::executeCanvasColor()";
	if (!checkParameterQuantity(node, 3, 20000+Token::CanvasColor*100+90) ||
		!checkParameterType(node, Value::Number, 20000+Token::CanvasColor*100+91)) return;
	emit canvasColor(node->child(0)->value()->number(), node->child(1)->value()->number(), node->child(2)->value()->number());
}
void Executer::executeSpriteShow(TreeNode* node) {
//	qDebug() << "Executer::executeSpriteShow()";
	if (!checkParameterQuantity(node, 0, 20000+Token::SpriteShow*100+90)) return;
	emit spriteShow();
}
void Executer::executeSpriteHide(TreeNode* node) {
//	qDebug() << "Executer::executeSpriteHide()";
	if (!checkParameterQuantity(node, 0, 20000+Token::SpriteHide*100+90)) return;
	emit spriteHide();
}
void Executer::executePrint(TreeNode* node) {
//	qDebug() << "Executer::executePrint()";
	if (!checkParameterQuantity(node, 1, 20000+Token::Print*100+90))
		return;
	qDebug() << "Printing: '" << node->child(0)->value()->string() << "'";
	emit print(node->child(0)->value()->string());
}
void Executer::executeFontSize(TreeNode* node) {
//	qDebug() << "Executer::executeFontSize()";
	if (!checkParameterQuantity(node, 1, 20000+Token::FontSize*100+90) ||
		!checkParameterType(node, Value::Number, 20000+Token::FontSize*100+91)) return;
	emit fontSize(node->child(0)->value()->number());
}
void Executer::executeRandom(TreeNode* node) {
//	qDebug() << "Executer::executeRandom()";
	if (!checkParameterQuantity(node, 2, 20000+Token::Random*100+90)) return;
	TreeNode* nodeX = node->child(0);  // getting
	TreeNode* nodeY = node->child(1);
	execute(nodeX);  // executing
	execute(nodeY);
	
	if (!checkParameterType(node, Value::Number, 20000+Token::Random*100+91)) return;
	double x = nodeX->value()->number();
	double y = nodeY->value()->number();
	double r = (double)(KRandom::random()) / RAND_MAX;
	node->value()->setNumber(r * (y - x) + x);
}
void Executer::executeGetX(TreeNode* node) {
//	qDebug() << "Executer::executeGetX()";
	if (!checkParameterQuantity(node, 0, 20000+Token::GetX*100+90)) return;
	double value = 0;
	emit getX(value);
	node->value()->setNumber(value);
}
void Executer::executeGetY(TreeNode* node) {
//	qDebug() << "Executer::executeGetY()";
	if (!checkParameterQuantity(node, 0, 20000+Token::GetY*100+90)) return;
	double value = 0;
	emit getY(value);
	node->value()->setNumber(value);
}
void Executer::executeMessage(TreeNode* node) {
//	qDebug() << "Executer::executeMessage()";
	if (!checkParameterQuantity(node, 1, 20000+Token::Message*100+90)) return;
	emit message(node->child(0)->value()->string());
}
void Executer::executeAsk(TreeNode* node) {
//	qDebug() << "Executer::executeAsk()";
	if (!checkParameterQuantity(node, 1, 20000+Token::Ask*100+90)) return;
	QString value = node->child(0)->value()->string();
	emit ask(value);
	node->value()->setString(value);
}
void Executer::executePi(TreeNode* node) {
//	qDebug() << "Executer::executePi()";
	node->value()->setNumber(M_PI);
}
void Executer::executeTan(TreeNode* node) {
//	qDebug() << "Executer::executeTan()";
	if (!checkParameterQuantity(node, 1, 20000+Token::Tan*100+90)) return;
	
	double deg = node->child(0)->value()->number();
	node->value()->setNumber(tan(DEG2RAD(deg)));
}
void Executer::executeSin(TreeNode* node) {
//	qDebug() << "Executer::executeSin()";
	if (!checkParameterQuantity(node, 1, 20000+Token::Sin*100+90)) return;
	
	double deg = node->child(0)->value()->number();
	node->value()->setNumber(sin(DEG2RAD(deg)));
}
void Executer::executeCos(TreeNode* node) {
//	qDebug() << "Executer::executeCos()";
	if (!checkParameterQuantity(node, 1, 20000+Token::Cos*100+90)) return;
	
	double deg = node->child(0)->value()->number();
	node->value()->setNumber(cos(DEG2RAD(deg)));
}
void Executer::executeArcTan(TreeNode* node) {
//	qDebug() << "Executer::executeArcTan()";
	if (!checkParameterQuantity(node, 1, 20000+Token::ArcTan*100+90)) return;
	
	double deg = node->child(0)->value()->number();
	node->value()->setNumber(RAD2DEG(atan(deg)));
}
void Executer::executeArcSin(TreeNode* node) {
//	qDebug() << "Executer::executeArcSin()";
	if (!checkParameterQuantity(node, 1, 20000+Token::ArcSin*100+90)) return;
	
	double deg = node->child(0)->value()->number();
	node->value()->setNumber(RAD2DEG(asin(deg)));
}
void Executer::executeArcCos(TreeNode* node) {
//	qDebug() << "Executer::executeArcCos()";
	if (!checkParameterQuantity(node, 1, 20000+Token::ArcCos*100+90)) return;
	
	double deg = node->child(0)->value()->number();
	node->value()->setNumber(RAD2DEG(acos(deg)));
}
void Executer::executeSqrt(TreeNode* node) {
//	qDebug() << "Executer::executeSqrt()";
	if (!checkParameterQuantity(node, 1, 20000+Token::Sqrt*100+90)) return;
	
	double val = node->child(0)->value()->number();
	node->value()->setNumber(sqrt(val));
}
void Executer::executeExp(TreeNode* node) {
//	qDebug() << "Executer::executeExp()";
	if (!checkParameterQuantity(node, 1, 20000+Token::Exp*100+90)) return;
	
	double val = node->child(0)->value()->number();
	node->value()->setNumber(exp(val));
}

//END GENERATED executer_cpp CODE


#include "executer.moc"
