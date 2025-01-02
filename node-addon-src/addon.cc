#include "node_modules/node-addon-api/napi.h"
#include <cerrno>
#include <napi.h>
#include <sys/types.h>

#ifdef __APPLE__
extern "C" ssize_t getxattr(const char *path, const char *name, void *value,
                            size_t size, u_int32_t position, int options);
#elif __linux__
extern "C" ssize_t getxattr(const char *path, const char *name, void *value,
                            size_t size);
#endif

Napi::Value GetXAttr(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();

  if (info.Length() < 2) {
    Napi::TypeError::New(env, "Wrong number of arguments")
        .ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsString() || !info[1].IsString()) {
    Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  std::string path = info[0].As<Napi::String>();
  std::string name = info[1].As<Napi::String>();

  const char *pathC = path.c_str();
  const char *nameC = name.c_str();

  char *buffer = new char[1024];
#ifdef __APPLE__
  int result = getxattr(pathC, nameC, buffer, 1024, 0, 0);
#elif __linux__
  int result = getxattr(pathC, nameC, buffer, 1024);
#endif

  if (result == -1) {
    const char *error = strerror(errno);
    Napi::Error::New(env, error).ThrowAsJavaScriptException();
    return env.Null();
  }

  Napi::String value = Napi::String::New(env, buffer, result);
  delete[] buffer;

  return value;
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "getxattr"),
              Napi::Function::New(env, GetXAttr));
  return exports;
}

NODE_API_MODULE(addon, Init)
