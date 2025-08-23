#include "history_tree.h"
#include "../kernel/boolean.h"
#include "../kernel/mesh.h"

namespace model {

HistoryTree::~HistoryTree() {
    free_mesh(&geometry_);
}

void HistoryTree::addFeature(const std::shared_ptr<Feature>& feature) {
    feature->setOnChanged([this]() { evaluate(); });
    features_.push_back(feature);
    evaluate();
}

void HistoryTree::evaluate() {
    Mesh result{};
    bool first = true;
    for (const auto &f : features_) {
        Mesh geom = f->generate();
        if (first) {
            result = geom;
            first = false;
        } else {
            Mesh combined = boolean_union(result, geom);
            free_mesh(&result);
            free_mesh(&geom);
            result = combined;
        }
    }
    free_mesh(&geometry_);
    geometry_ = result;
}

} // namespace model

