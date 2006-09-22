/*
	Copyright (C) 2003-2006 Cies Breijs <cies # kde ! nl>

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


#ifndef _ECHOER_H_
#define _ECHOER_H_


#include <QTextStream>

#include "executer.h"

/**
 * @short Echoes signals to a QTextStream
 *
 * Just echos the signals it gets.
 * Usefull for creating UnitTests.
 *
 * @author Cies Breijs
 */
class Echoer : public QObject
{
	Q_OBJECT

	public:
		/**
		 * Default Constructor
		 */
		Echoer(QTextStream& outputStream, QObject* parent = 0) {
			setParent(parent);
			output = &outputStream;
			reset();
		};

		/**
		 * Default Destructor
		 */
		virtual ~Echoer() {};

		/**
		 * Connects all its slots to the signals of the Executer
		 */
		void connectAllSlots(Executer* executer) {
			// these connect calls connect all the Executers signals to this class' slots

//BEGIN GENERATED echoer_connect_h CODE

/* The code between the line that start with "//BEGIN GENERATED" and "//END GENERATED"
 * is generated by "generate.rb" according to the definitions specified in
 * "definitions.rb". Please make all changes in the "definitions.rb" file, since all
 * all change you make here will be overwritten the next time "generate.rb" is run.
 * Thanks for looking at the code!
 */

			connect(executer, SIGNAL(reset()), 
				SLOT(reset()));
			connect(executer, SIGNAL(clear()), 
				SLOT(clear()));
			connect(executer, SIGNAL(center()), 
				SLOT(center()));
			connect(executer, SIGNAL(go(double, double)), 
				SLOT(go(double, double)));
			connect(executer, SIGNAL(goX(double)), 
				SLOT(goX(double)));
			connect(executer, SIGNAL(goY(double)), 
				SLOT(goY(double)));
			connect(executer, SIGNAL(forward(double)), 
				SLOT(forward(double)));
			connect(executer, SIGNAL(backward(double)), 
				SLOT(backward(double)));
			connect(executer, SIGNAL(direction(double)), 
				SLOT(direction(double)));
			connect(executer, SIGNAL(turnLeft(double)), 
				SLOT(turnLeft(double)));
			connect(executer, SIGNAL(turnRight(double)), 
				SLOT(turnRight(double)));
			connect(executer, SIGNAL(penWidth(double)), 
				SLOT(penWidth(double)));
			connect(executer, SIGNAL(penUp()), 
				SLOT(penUp()));
			connect(executer, SIGNAL(penDown()), 
				SLOT(penDown()));
			connect(executer, SIGNAL(penColor(double, double, double)), 
				SLOT(penColor(double, double, double)));
			connect(executer, SIGNAL(canvasColor(double, double, double)), 
				SLOT(canvasColor(double, double, double)));
			connect(executer, SIGNAL(canvasSize(double, double)), 
				SLOT(canvasSize(double, double)));
			connect(executer, SIGNAL(spriteShow()), 
				SLOT(spriteShow()));
			connect(executer, SIGNAL(spriteHide()), 
				SLOT(spriteHide()));
			connect(executer, SIGNAL(print(QString)), 
				SLOT(print(QString)));
			connect(executer, SIGNAL(fontSize(double)), 
				SLOT(fontSize(double)));

//END GENERATED echoer_connect_h CODE
		}


	private:
		QTextStream* output;


	public slots:
		// the generated code is a set of slots that are covering all the Executers signals...

//BEGIN GENERATED echoer_slots_h CODE

/* The code between the line that start with "//BEGIN GENERATED" and "//END GENERATED"
 * is generated by "generate.rb" according to the definitions specified in
 * "definitions.rb". Please make all changes in the "definitions.rb" file, since all
 * all change you make here will be overwritten the next time "generate.rb" is run.
 * Thanks for looking at the code!
 */

		void reset() { *output << "reset" << "(" << ")\n"; }
		void clear() { *output << "clear" << "(" << ")\n"; }
		void center() { *output << "center" << "(" << ")\n"; }
		void go(double arg0, double arg1) { *output << "go" << "(" << arg0 << "," << arg1 << ")\n"; }
		void goX(double arg0) { *output << "goX" << "(" << arg0 << ")\n"; }
		void goY(double arg0) { *output << "goY" << "(" << arg0 << ")\n"; }
		void forward(double arg0) { *output << "forward" << "(" << arg0 << ")\n"; }
		void backward(double arg0) { *output << "backward" << "(" << arg0 << ")\n"; }
		void direction(double arg0) { *output << "direction" << "(" << arg0 << ")\n"; }
		void turnLeft(double arg0) { *output << "turnLeft" << "(" << arg0 << ")\n"; }
		void turnRight(double arg0) { *output << "turnRight" << "(" << arg0 << ")\n"; }
		void penWidth(double arg0) { *output << "penWidth" << "(" << arg0 << ")\n"; }
		void penUp() { *output << "penUp" << "(" << ")\n"; }
		void penDown() { *output << "penDown" << "(" << ")\n"; }
		void penColor(double arg0, double arg1, double arg2) { *output << "penColor" << "(" << arg0 << "," << arg1 << "," << arg2 << ")\n"; }
		void canvasColor(double arg0, double arg1, double arg2) { *output << "canvasColor" << "(" << arg0 << "," << arg1 << "," << arg2 << ")\n"; }
		void canvasSize(double arg0, double arg1) { *output << "canvasSize" << "(" << arg0 << "," << arg1 << ")\n"; }
		void spriteShow() { *output << "spriteShow" << "(" << ")\n"; }
		void spriteHide() { *output << "spriteHide" << "(" << ")\n"; }
		void print(QString arg0) { *output << "print" << "(" << arg0 << ")\n"; }
		void fontSize(double arg0) { *output << "fontSize" << "(" << arg0 << ")\n"; }

//END GENERATED echoer_slots_h CODE

};

#endif  // _ECHOER_H_


