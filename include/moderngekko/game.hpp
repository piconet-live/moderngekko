#pragma once

#include <cstdint>
#include <filesystem>
#include <optional>
#include <string>

namespace moderngekko
{
enum class GamePlatform
{
  GameCube,
  Wii,
};

struct GameMetadata
{
  std::filesystem::path root;
  std::filesystem::path main_dol;
  std::filesystem::path main_rel;
  std::string game_name;
  std::string disc_id;
  GamePlatform platform = GamePlatform::GameCube;
  std::uint32_t entry_point = 0;
  std::string dol_sha256;
  std::string rel_sha256;
  std::string assets_sha256;
};

struct GameInspectResult
{
  std::optional<GameMetadata> metadata;
  std::string error;

  explicit operator bool() const { return metadata.has_value(); }
};

// Whether InspectGame hashes every file under files/ into assets_sha256. That reads the whole game (1.4 GB and
// twenty seconds for F-Zero GX on an NVMe disk); a caller that does not compare the hash skips it and gets an
// empty assets_sha256.
enum class GameAssets
{
  Hash,
  Skip,
};

GameInspectResult InspectGame(const std::filesystem::path& root,
                              GameAssets assets = GameAssets::Hash);
std::optional<std::string> HashFileSha256(const std::filesystem::path& path);
std::optional<std::string> HashDirectorySha256(const std::filesystem::path& root);
}  // namespace moderngekko

namespace ModernGekko = moderngekko;
