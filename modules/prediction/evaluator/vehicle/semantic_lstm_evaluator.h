/******************************************************************************
 * Copyright 2019 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "torch/extension.h"
#include "torch/script.h"

#include "modules/prediction/evaluator/evaluator.h"

namespace apollo {
namespace prediction {

class SemanticLSTMEvaluator : public Evaluator {
 public:
  /**
   * @brief Constructor
   */
  SemanticLSTMEvaluator();

  /**
   * @brief Destructor
   */
  virtual ~SemanticLSTMEvaluator() = default;

  /**
   * @brief Clear obstacle feature map
   */
  void Clear();

  /**
   * @brief Override Evaluate
   * @param Obstacle pointer
   */
  bool Evaluate(Obstacle* obstacle_ptr) override;

  /**
   * @brief Extract feature vector
   * @param Obstacle pointer
   *        Feature container in a vector for receiving the feature values
   */
  bool ExtractFeatureValues(Obstacle* obstacle_ptr,
                            std::vector<double>* feature_values);

  /**
   * @brief Get the name of evaluator.
   */
  std::string GetName() override { return "SEMANTIC_LSTM_EVALUATOR"; }

 private:
  /**
   * @brief Load model file
   */
  void LoadModel();

 private:
  static const size_t OBSTACLE_FEATURE_SIZE = 20 * 2;
  torch::jit::script::Module torch_model_;
  torch::Device device_;
};

}  // namespace prediction
}  // namespace apollo