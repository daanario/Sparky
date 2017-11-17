#pragma once
#include <string>
#include <fstream>
namespace sparky {

	/* Vores game engine skal kunne l�se filer som f.eks. shaders. Vi bruger FILE fra C-biblioteket string, da det er ekstremt hurtigt. "rt" st�r for read-only, text. Dette er vigtigt da vi kun skal l�se filen, og den skal genkende, at der er forskellige linjer, s� den ikke l�ser alt p� �n linje */

	class FileUtils
	{
	public:
		static std::string read_file(const char* filepath)
		{
			FILE* file = fopen(filepath, "rt");
			fseek(file, 0, SEEK_END);
			unsigned long length = ftell(file);
			char* data = new char[length + 1]; //der l�gges 1 til, s� man kan bruge en terminator
			memset(data, 0, length + 1);
			fseek(file, 0, SEEK_SET);
			fread(data, 1, length, file);
			fclose(file);

			std::string result(data);
			delete[] data;
			return result;
		}
	};


}
