#include "BvhParser.hpp"
#include <iostream>
#include <sstream>
namespace dart {
namespace io {
namespace BvhParser{

	dynamics::BodyNode* readBodyNode(dynamics::BodyNode* parent,std::istream& is);


std::pair<std::vector<Eigen::VectorXd>,double> readMotion(
	const common::Uri& _uri,
	const common::ResourceRetrieverPtr& retrieverOrNullPtr)
{
	std::pair<std::vector<Eigen::VectorXd>,double> motion;
	common::ResourceRetrieverPtr retriever;
	if(retrieverOrNullPtr)
    retriever = retrieverOrNullPtr;
  else
    retriever = std::make_shared<common::LocalResourceRetriever>();

  const auto content = retriever->readAll(_uri);
  // if(content.find("MOTION")==std::string::npos)
  // {
  // 	std::cout<<content<<std::endl;
  // }
  std::string motion_content = content.substr(content.find("MOTION"));

  std::istringstream motion_all;
  motion_all.str(motion_content);
  std::string line;
  std::getline(motion_all,line);
  std::getline(motion_all,line);
  std::stringstream ss;
  ss.clear();
  ss.str(line);
  std::string index;
  double num_frames,time_step;
  ss>>index;
  ss>>num_frames;

  std::getline(motion_all,line);
  ss.clear();
  ss.str(line);
  ss>>index;
  ss>>index;
  ss>>time_step;

	motion.first.resize(num_frames);
	motion.second = time_step;

	int count = 0;
  while(std::getline(motion_all,line))
  {
  	motion.first[count++] = toVectorXd(line);
  }
  return motion;
}




dynamics::SkeletonPtr readSkeleton(
	const common::Uri& _uri,
	const common::ResourceRetrieverPtr& retrieverOrNullPtr)
{
  common::ResourceRetrieverPtr retriever;
	if(retrieverOrNullPtr)
    retriever = retrieverOrNullPtr;
  else
    retriever = std::make_shared<common::LocalResourceRetriever>();

  const auto content = retriever->readAll(_uri);
  std::size_t start = content.find("HIERARCHY");
  std::size_t end = content.find("MOTION");

  std::string skeleton_content;
  if(end!=std::string::npos)
  	skeleton_content = content.substr(start,end-start);
	else
		skeleton_content = content;

	std::cout<<skeleton_content<<std::endl;

  std::istringstream skel_all;
  skel_all.str(skeleton_content);
  std::string line;
	
	//HIERARCHY  
  std::getline(skel_all,line);
  readBodyNode(nullptr,skel_all);
	return nullptr;
}
dynamics::BodyNode* readBodyNode(dynamics::BodyNode* parent,std::istream& is)
{
	std::string line,token,body_name;
	std::stringstream ss;
	std::getline(is,line);
	ss.str(line);
	ss>>token;
	ss>>body_name;

	std::getline(is,line);	//{
	std::getline(is,line);	//OFFSET
	ss.str(line);
	ss>>token;
	double x,y,z;
	ss>>x>>y>>z;
	std::getline(is,line);	//CHANNELS
	ss.str(line);
	ss>>token;
	if(token.find("}")!=std::string::npos)	//No Joint
		return nullptr;
	int num_dof;
	ss>>num_dof;
	if(num_dof==6) 													//Free Joint
	{
		dynamics::FreeJoint::Properites prop;
		prop.mName = body_name+"_joint";
		prop.m
	}
	else if(num_dof==3)											//Ball Joint
	{
		dynamics::BallJoint::Properites prop;
		prop.mName = body_name+"_joint";
	}
	//exception case : End Site
	

	while(true)
	{
		auto cur_pos = is.tellg();
		std::getline(is,line);
		ss.str(line);
		ss>>token;
		if(token.find("}")!=std::string::npos)
			break;
		else
		{
			is.seekg(cur_pos);
			readBodyNode(nullptr,is);
		}
	}

	return nullptr;
}

} // namespace BvhParser
} // namespace io
} // namespace dart
