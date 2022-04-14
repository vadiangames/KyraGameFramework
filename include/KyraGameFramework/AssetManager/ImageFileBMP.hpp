#ifndef KYRAGAMEFRAMEWORK_ASSETMANAGER_IMAGEFILEBMP_HPP
#define KYRAGAMEFRAMEWORK_ASSETMANAGER_IMAGEFILEBMP_HPP

#include <vector>
#include <filesystem>
#include <fstream>

//SOURCE: https://solarianprogrammer.com/2018/11/19/cpp-reading-writing-bmp-images/

namespace kyra {
	
	#pragma pack(push,1)
	
	typedef struct {
		uint16_t type{0x4042};
		uint32_t size{0};
		uint16_t reserved1{0};
		uint16_t reserved2{0};
		uint32_t offsetData{0};
	}BMPFileHeader;
	
	typedef struct {
		uint32_t size{0};
		int32_t width{0};
		int32_t height{0};
		uint16_t planes{1};
		uint16_t bitCount{0};
		uint32_t compression{0};
		uint32_t sizeImage{0};
		int32_t xPixelsPerMeter{0};
		int32_t yPixelsPerMeter{0};
		uint32_t colorsUsed{0};
		uint32_t colorsImportant{0};
	}BMPInfoHeader;

	typedef struct {
		uint32_t redMask{0x00ff0000};
		uint32_t greenMask{0x0000ff00};
		uint32_t blueMask{0x000000ff};
		uint32_t alphaMask{0xff000000};
		uint32_t colorSpaceType{ 0x73524742 };
		uint32_t unused[16]{0};
	}BMPColorHeader;
	
	#pragma pack(pop)
	
	class ImageFileBMP {
		
		public:
		
		BMPFileHeader m_Header;
		BMPInfoHeader m_InfoHeader;
		BMPColorHeader m_ColorHeader;
		std::vector<uint8_t> m_Data;
		
		uint32_t m_RowStride;
		
		bool checkColorHeader(const BMPColorHeader& header) {
			
			//TODO: Implementation
			
			return true;
		}
		
		uint32_t makeStrideAligned(uint32_t rowStride, uint32_t alignStride) {
			uint32_t newStride = rowStride;
			while(newStride % alignStride != 0) {
				newStride++;
			}
			return newStride;
		}
		
		void writeHeaders(std::ofstream& of) {
			of.write( (const char*)(&m_Header), sizeof(BMPFileHeader));
			of.write( (const char*)(&m_InfoHeader), sizeof(BMPInfoHeader));
			//if(m_InfoHeader.bitCount == 32) {
				of.write((const char*)(&m_ColorHeader), sizeof(BMPColorHeader));
			//}
		}
		
		void writeHeadersAndData(std::ofstream& of) {
			writeHeaders(of);
			of.write((const char*)(m_Data.data()), m_Data.size());
		}
		
		//public:
		ImageFileBMP() : m_RowStride(0) {}
		ImageFileBMP(int32_t width, int32_t height, bool hasAlpha = true) {}
		~ImageFileBMP() {}
		
		bool load(const std::filesystem::path& filePath ) {
			
			//TODO: Check if file exists
			
			std::ifstream file{filePath.string().c_str(), std::ios_base::binary};
			
			if(!file) {
				return false;
			}
			
			file.read((char*)&m_Header, sizeof(BMPFileHeader));
			
			std::cout << "[BMPFileHeader]" << std::endl;
			std::cout << "Type: " << m_Header.type << std::endl;
			std::cout << "Size: " << m_Header.size << std::endl;
			std::cout << "Offset-Data: " << m_Header.offsetData << std::endl;
		
			if(m_Header.type != 0x4D42) {
				file.close();
				return false;
			}
				
			file.read((char*)&m_InfoHeader, sizeof(BMPInfoHeader));
			
			std::cout << "[BMPInfoHeader]" << std::endl;
			std::cout << "Size: " << m_InfoHeader.size << std::endl;
			std::cout << "Width: " << m_InfoHeader.width << std::endl;
			std::cout << "Height: " << m_InfoHeader.height << std::endl;
			std::cout << "Planes: " << m_InfoHeader.planes << std::endl;
			std::cout << "BitCount: " << m_InfoHeader.bitCount << std::endl;
			std::cout << "Compression: " << m_InfoHeader.compression << std::endl;
			std::cout << "SizeImage: " << m_InfoHeader.sizeImage << std::endl;
			std::cout << "X-Pixels-Per-Meter: " << m_InfoHeader.xPixelsPerMeter << std::endl;
			std::cout << "Y-Pixels-Per-Meter: " << m_InfoHeader.yPixelsPerMeter << std::endl;
			std::cout << "Colors used: " << m_InfoHeader.colorsUsed << std::endl;
			std::cout << "Colors important: " << m_InfoHeader.colorsImportant << std::endl;
			
			if(m_InfoHeader.bitCount == 32) {
											
				file.read((char*)(&m_ColorHeader), sizeof(BMPColorHeader));
				std::cout << "[BMPInfoColorHeader]" << std::endl;
				std::cout << "GreenMask: " << m_ColorHeader.greenMask << std::endl;
				std::cout << "BlueMask: " << m_ColorHeader.blueMask << std::endl;
				std::cout << "AlphaMask: " << m_ColorHeader.alphaMask << std::endl;
				std::cout << "ColorSpaceType: " << m_ColorHeader.colorSpaceType << std::endl;
			
			}
			
			file.seekg(m_Header.offsetData, file.beg);
			
			if(m_InfoHeader.bitCount == 32) {
				m_InfoHeader.size = sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);
				m_Header.offsetData = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);
			} else {
				m_InfoHeader.size = sizeof(BMPInfoHeader);
				m_Header.offsetData = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);
			}
			
			m_Header.size = m_Header.offsetData;
			
			if(m_InfoHeader.size < 0) {
				file.close();
				return false;
			}
			
			m_Data.resize(m_InfoHeader.width * m_InfoHeader.height * m_InfoHeader.bitCount / 8);
			
			if(m_InfoHeader.width % 4 == 0) {
				file.read((char*)m_Data.data(), m_Data.size());
				m_Header.size += m_Data.size();
			} else {
				m_RowStride = m_InfoHeader.width * m_InfoHeader.bitCount / 8;
				uint32_t newStride = makeStrideAligned(m_RowStride,4);
				std::vector<uint8_t> paddingRow(newStride - m_RowStride);
				for(int y = 0; y < m_InfoHeader.height; ++y) {
					file.read((char*)(m_Data.data() + m_RowStride * y), m_RowStride);
					file.read((char*)paddingRow.data(), paddingRow.size());
				}
				m_Header.size += m_Data.size() + m_InfoHeader.height * paddingRow.size();
			}
			
		
			file.close();
			return true;
		}
		
		bool create(int32_t width, int32_t height, bool hasAlpha = true) {
			
			m_InfoHeader.width = width;
			m_InfoHeader.height = height;
			
			if(hasAlpha) {
				m_InfoHeader.size = sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);
				m_Header.offsetData = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);
				m_InfoHeader.bitCount = 32;
				m_InfoHeader.compression = 3;
				m_RowStride = width * 4;
				m_Data.resize(m_RowStride*height);
				m_Header.size = m_Header.offsetData + m_Data.size();
			}else {
				m_InfoHeader.size = sizeof(BMPInfoHeader);
				m_Header.offsetData = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);
				m_InfoHeader.bitCount = 24;
				m_InfoHeader.compression = 0;
				m_RowStride = width * 3;
				m_Data.resize(m_RowStride*height);
				uint32_t newStride = makeStrideAligned(m_RowStride,4);
				m_Header.size = m_Header.offsetData + m_Data.size() + m_InfoHeader.height * (newStride - m_RowStride);	
			}
			return true;
		}
		
		void write(const std::filesystem::path& file) {
			std::ofstream of(file.string().c_str(), std::ios_base::binary);
			if(of) {
				if(m_InfoHeader.bitCount == 32) {
					writeHeadersAndData(of);
				} else if(m_InfoHeader.bitCount == 24) {
					if(m_InfoHeader.width % 4 == 0) {
						writeHeadersAndData(of);
					} else {
						uint32_t newStride = makeStrideAligned(m_RowStride, 4);
						std::cout << "New Stride: " << newStride << std::endl;
						std::vector<uint8_t> paddingRow(newStride - m_RowStride);
						writeHeaders(of);
						std::cout << m_InfoHeader.height << std::endl;
						for(int y = 0; y < m_InfoHeader.height; ++y) {
							std::cout << y << std::endl;
							of.write((const char*)(m_Data.data() + m_RowStride * y), m_RowStride);
							of.write((const char*)(paddingRow.data()), paddingRow.size());
						}
					}
				}
				of.close();
			}
		}
				
		
	};
	
}




#endif