# 1. 下载 depot_tools
git clone https://chromium.googlesource.com/chromium/tools/depot_tools.git
export PATH="$PATH:$(pwd)/depot_tools"

# 2. 拉取 WebRTC 源码（约 15GB）
mkdir webrtc-checkout && cd webrtc-checkout
fetch --nohooks webrtc
cd src

# 3. 同步依赖（建议使用特定稳定版本，如 Google Meet API 示例中使用的 b00c469）
git checkout b00c469cad3f8c926fcf81ded90b90b6e1e62b9c
cd ..
gclient sync


