#include <string>
#include <vector>

namespace bookchain {
namespace storage {

constexpr char blockchainFilename[] = "theblock.chain";

void purgeChain(const std::string& filename);
void dumpChain(std::vector<Bloock> bloockChain, const std::string& filename);
std::vector<Bloock> getChain(const std::string& filename);

void appendChain(Bloock bloock, const std::string& filename);

Bloock getBlockByHeight(unsigned int blockHeight, const std::string& filename);

Bloock getBlockLatest(const std::string& filename);

int getChainHeight(const std::string& filename);

}  // namespace storage
}  // namespace bookchain
