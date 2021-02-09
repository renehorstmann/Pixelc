#include "brush_shape.h"

const char brush_shape_kernels
        [BRUSH_NUM_SHAPES]
        [BRUSH_KERNEL_SIZE][BRUSH_KERNEL_SIZE] = {
	{
		{0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 1, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0}
	},
	{
		{0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 1, 1, 0, 0},
		{0, 0, 0, 1, 1, 0, 0},
		{0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0}
	},
	{
		{0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 1, 0, 0, 0},
		{0, 0, 1, 1, 1, 0, 0},
		{0, 0, 0, 1, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0}
	},
	{
		{0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0},
		{0, 0, 1, 1, 1, 0, 0},
		{0, 0, 1, 1, 1, 0, 0},
		{0, 0, 1, 1, 1, 0, 0},
		{0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0}
	},
	{
		{0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 1, 1, 0, 0},
		{0, 0, 1, 1, 1, 1, 0},
		{0, 0, 1, 1, 1, 1, 0},
		{0, 0, 0, 1, 1, 0, 0},
		{0, 0, 0, 0, 0, 0, 0}
	},
	{
		{0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 1, 0, 0, 0},
		{0, 0, 1, 1, 1, 0, 0},
		{0, 1, 1, 1, 1, 1, 0},
		{0, 0, 1, 1, 1, 0, 0},
		{0, 0, 0, 1, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0}
	},
	{
		{0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0},
		{0, 0, 1, 1, 1, 1, 0},
		{0, 0, 1, 1, 1, 1, 0},
		{0, 0, 1, 1, 1, 1, 0},
		{0, 0, 1, 1, 1, 1, 0},
		{0, 0, 0, 0, 0, 0, 0}
	},
	{
		{0, 0, 0, 0, 0, 0, 0},
		{0, 0, 1, 1, 1, 0, 0},
		{0, 1, 1, 1, 1, 1, 0},
		{0, 1, 1, 1, 1, 1, 0},
		{0, 1, 1, 1, 1, 1, 0},
		{0, 0, 1, 1, 1, 0, 0},
		{0, 0, 0, 0, 0, 0, 0}
	},
	{
		{0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 1, 1, 0, 0},
		{0, 0, 1, 1, 1, 1, 0},
		{0, 1, 1, 1, 1, 1, 1},
		{0, 1, 1, 1, 1, 1, 1},
		{0, 0, 1, 1, 1, 1, 0},
		{0, 0, 0, 1, 1, 0, 0}
	},
	{
		{0, 0, 0, 0, 0, 0, 0},
		{0, 1, 1, 1, 1, 1, 0},
		{0, 1, 1, 1, 1, 1, 0},
		{0, 1, 1, 1, 1, 1, 0},
		{0, 1, 1, 1, 1, 1, 0},
		{0, 1, 1, 1, 1, 1, 0},
		{0, 0, 0, 0, 0, 0, 0}
	},
	{
		{0, 0, 0, 1, 0, 0, 0},
		{0, 1, 1, 1, 1, 1, 0},
		{0, 1, 1, 1, 1, 1, 0},
		{1, 1, 1, 1, 1, 1, 1},
		{0, 1, 1, 1, 1, 1, 0},
		{0, 1, 1, 1, 1, 1, 0},
		{0, 0, 0, 1, 0, 0, 0}
	},
	{
		{0, 0, 0, 0, 0, 0, 0},
		{0, 0, 1, 1, 1, 1, 0},
		{0, 1, 1, 1, 1, 1, 1},
		{0, 1, 1, 1, 1, 1, 1},
		{0, 1, 1, 1, 1, 1, 1},
		{0, 1, 1, 1, 1, 1, 1},
		{0, 0, 1, 1, 1, 1, 0}
	},
	{
		{0, 0, 0, 0, 0, 0, 0},
		{0, 1, 1, 1, 1, 1, 1},
		{0, 1, 1, 1, 1, 1, 1},
		{0, 1, 1, 1, 1, 1, 1},
		{0, 1, 1, 1, 1, 1, 1},
		{0, 1, 1, 1, 1, 1, 1},
		{0, 1, 1, 1, 1, 1, 1}
	},
	{
		{0, 0, 1, 1, 1, 0, 0},
		{0, 1, 1, 1, 1, 1, 0},
		{1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1},
		{0, 1, 1, 1, 1, 1, 0},
		{0, 0, 1, 1, 1, 0, 0}
	},
	{
		{0, 1, 1, 1, 1, 1, 0},
		{1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1},
		{0, 1, 1, 1, 1, 1, 0}
	},
	{
		{1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1}
	}
	
};
