#ifndef KYRAGAMEFRAMEWORK_GRAPHICS_TYPES_HPP
#define KYRAGAMEFRAMEWORK_GRAPHICS_TYPES_HPP

namespace kyra {
	
	enum class DataType {
		UNKNOWN,
		FLOAT
	};
	
	enum class PrimitiveType {
		UNKNOWN,
		TRIANGLES
	};
	
	enum class BufferType {
		STATIC_DRAW,
		DYNAMIC_DRAW
	};
		
}

#endif