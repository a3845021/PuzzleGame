/*
* Template.h
*
*  Created on: 23.02.2016
*      Author: User
*/

#ifndef _TEMPLATE_H_
#define _TEMPLATE_H_

#define NUM_POS 4
#define NUM_ELEMENT_TYPES 6
#define GRID_LENGTH 3


struct ElementStructure {
	int angle;
	char *grid[GRID_LENGTH];
};

// массив элементов для каждго положения в пространстве
// значение (пробел или X)
const ElementStructure elementTemplates[NUM_ELEMENT_TYPES][NUM_POS] =
{
	{
		{ 0,	"   ",
				"   ",
				"   " },
		{ 90,	"   ",
				"   ",
				"   " },
		{ 180,	"   ",
				"   ",
				"   " },
		{ 270,	"   ",
				"   ",
				"   " }
	},
	{
		{ 0,	" X ",
				" X ",
				"   " },
		{ 90,	" X ",
				" X ",
				"   " },
		{ 180,	" X ",
				" X ",
				"   " },
		{ 270,	" X ",
				" X ",
				"   " }
	},
	{
		{ 0,	" X ",
				" X ",
				"   " },
		{ 90,	" X ",
				" X ",
				"   " },
		{ 180,	" X ",
				" X ",
				"   " },
		{ 270,	" X ",
				" X ",
				"   " }
	},
	{
		{ 0,	" X ",
				" X ",
				" X " },

		{ 90,	"   ",
				"XXX",
				"   " },

		{ 180,	" X ",
				" X ",
				" X " },

		{ 270,	"   ",
				"XXX",
				"   " }
	},
	{
		{ 0,	" X ",
				" XX",
				"   " },

		{ 90,	"   ",
				" XX",
				" X " },

		{ 180,	"   ",
				"XX ",
				" X " },

		{ 270,	" X ",
				"XX ",
				"   " }
	},
	{
		{ 0,	" X ",
				" XX",
				" X "},

		{ 90,	"   ",
				"XXX",
				" X "},

		{ 180,	" X ",
				"XX ",
				" X "},

		{ 270,	" X ",
				"XXX",
				"   " }
	}

};

#endif