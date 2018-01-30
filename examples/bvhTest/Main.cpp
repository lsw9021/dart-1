#include <dart/io/io.hpp>
#include <dart/dart.hpp>


int main(int argc, char* argv[]) {
	// dart::io::BvhParser::readSkeleton("file:///home/seunghwan/Desktop/move.bvh");
	auto skel = dart::io::BvhParser::readSkeleton("/home/seunghwan/Desktop/move.bvh");
	auto motion = dart::io::BvhParser::readMotion("/home/seunghwan/Desktop/move.bvh");

	std::cout<<motion.first.size()<<std::endl;
	std::cout<<motion.second<<std::endl;

	return 0;
}