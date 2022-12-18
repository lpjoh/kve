#pragma once
#ifdef KVE_GL

namespace kve {
	constexpr int glInfoLogSize = 512;

	class GL {
	public:
		static char infoLog[glInfoLogSize];
		static int success;
	};
}

#endif