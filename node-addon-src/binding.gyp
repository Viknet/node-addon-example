{
  "targets": [
    {
      "target_name": "addon",
      'cflags!': [ '-fno-exceptions' ],
      'cflags_cc!': [ '-fno-exceptions' ],
      "sources": [ "addon.cc" ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      'defines': [ 'NODE_ADDON_API_CPP_EXCEPTIONS', 'NODE_ADDON_API_CPP_EXCEPTIONS_ALL' ],
      'conditions': [
        ["OS=='mac'", {
            'xcode_settings': {
                'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
                'CLANG_CXX_LIBRARY': 'libc++',
                'MACOSX_DEPLOYMENT_TARGET': '11.0',
            },
        }],
    ],
    }
  ]
}
