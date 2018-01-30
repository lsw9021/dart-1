#ifndef DART_IO_BVHPARSER_HPP_
#define DART_IO_BVHPARSER_HPP_

#include <string>
#include "dart/common/Uri.hpp"
#include "dart/common/LocalResourceRetriever.hpp"
#include "dart/simulation/World.hpp"
#include "dart/io/XmlHelpers.hpp"
namespace dart{
namespace io{
namespace BvhParser{

	std::pair<std::vector<Eigen::VectorXd>,double> readMotion(
		const common::Uri& _uri,
		const common::ResourceRetrieverPtr& retriever = nullptr);

	dynamics::SkeletonPtr readSkeleton(
		const common::Uri& uri,
		const common::ResourceRetrieverPtr& retriever = nullptr);
} // namespace BvhParser
} // namespace io
} // namespace dart
#endif