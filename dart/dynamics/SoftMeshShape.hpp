/*
 * Copyright (c) 2013-2016, Georgia Tech Research Corporation
 * All rights reserved.
 *
 * Author(s): Jeongseok Lee <jslee02@gmail.com>
 *
 * Georgia Tech Graphics Lab and Humanoid Robotics Lab
 *
 * Directed by Prof. C. Karen Liu and Prof. Mike Stilman
 * <karenliu@cc.gatech.edu> <mstilman@cc.gatech.edu>
 *
 * This file is provided under the following "BSD-style" License:
 *   Redistribution and use in source and binary forms, with or
 *   without modification, are permitted provided that the following
 *   conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 *   CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 *   INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *   MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 *   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 *   USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 *   AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *   ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *   POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef DART_DYNAMICS_SOFTMESHSHAPE_HPP_
#define DART_DYNAMICS_SOFTMESHSHAPE_HPP_

#include <assimp/scene.h>
#include <Eigen/Dense>
#include "dart/dynamics/Shape.hpp"

namespace dart {
namespace dynamics {

class SoftBodyAspect;

// TODO(JS): Implement
class SoftMeshShape : public Shape
{
public:

  friend class SoftBodyAspect;

  /// \brief Constructor.
  explicit SoftMeshShape(SoftBodyAspect* softBodyAspect);

  /// \brief Destructor.
  virtual ~SoftMeshShape();

  /// \brief
  const aiMesh* getAssimpMesh() const;

  /// Get the SoftBodyNode that is associated with this SoftMeshShape
  const SoftBodyAspect* getSoftBodyAspect() const;

  /// \brief Update positions of the vertices using the parent soft body node.
  void update();

  // Documentation inherited.
  Eigen::Matrix3d computeInertia(double mass) const override;

protected:
  // Documentation inherited.
  void updateVolume() override;

private:
  /// \brief Build mesh using SoftBodyNode data
  void _buildMesh();

  /// \brief
  SoftBodyAspect* mSoftBodyAspect;

  /// \brief
  std::unique_ptr<aiMesh> mAssimpMesh;
};

}  // namespace dynamics
}  // namespace dart

#endif  // DART_DYNAMICS_SOFTMESHSHAPE_HPP_