#pragma once
#include <string>
#include <optional>

namespace kve {
	class IO {
	public:
		static std::optional<std::string> LoadFileString(const std::string filePath);
	};
}