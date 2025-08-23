#pragma once
#include <vector>
#include <memory>
#include "feature.h"
#include "../kernel/mesh.h"

namespace model {

class HistoryTree {
public:
    HistoryTree() = default;
    ~HistoryTree();

    void addFeature(const std::shared_ptr<Feature>& feature);
    void evaluate();
    const Mesh& geometry() const { return geometry_; }

private:
    std::vector<std::shared_ptr<Feature>> features_;
    Mesh geometry_{};
};

} // namespace model

