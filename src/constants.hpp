#pragma once

#include <string>

using namespace std;

namespace Constants {
inline string GetAssetPath(string assetName) {
  return ASSETS_PATH "" + assetName;
}
}  // namespace AppConstants