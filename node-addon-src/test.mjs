import { createRequire } from "module";
const require = createRequire(import.meta.url);
var addon = require("./build/Release/addon.node");

console.log("This should be eight:", addon.getxattr("/Users/viknet/Downloads/steam.dmg", "com.apple.quarantine"));
