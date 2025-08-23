#include <vector>
#include <memory>
#include <string>
#include <functional>

// Simple representation of geometry for demonstration purposes.
struct Geometry {
    std::vector<std::string> operations; // sequence of operations applied
};

// Base class for all modeling features.
class Feature {
public:
    virtual ~Feature() = default;

    // Evaluate this feature and append to geometry.
    virtual void evaluate(Geometry &geom) = 0;

    // Called by HistoryTree to register callback when parameters change.
    void setOnChanged(std::function<void()> cb) { onChanged_ = std::move(cb); }

protected:
    // Utility to notify tree when parameters were modified.
    void notifyChanged() {
        if (onChanged_) onChanged_();
    }

private:
    std::function<void()> onChanged_;
};

// Feature that extrudes a profile with adjustable height.
class ExtrudeFeature : public Feature {
public:
    explicit ExtrudeFeature(double h) : height_(h) {}

    void setHeight(double h) {
        height_ = h;
        notifyChanged();
    }

    double height() const { return height_; }

    void evaluate(Geometry &geom) override {
        geom.operations.push_back("Extrude:" + std::to_string(height_));
    }

private:
    double height_;
};

// Feature that fillets an edge with adjustable radius.
class FilletFeature : public Feature {
public:
    explicit FilletFeature(double r) : radius_(r) {}

    void setRadius(double r) {
        radius_ = r;
        notifyChanged();
    }

    double radius() const { return radius_; }

    void evaluate(Geometry &geom) override {
        geom.operations.push_back("Fillet:" + std::to_string(radius_));
    }

private:
    double radius_;
};

// History tree that maintains an ordered sequence of features.
class HistoryTree {
public:
    // Add a new feature to the tree and evaluate.
    void addFeature(const std::shared_ptr<Feature> &feature) {
        feature->setOnChanged([this]() { evaluate(); });
        features_.push_back(feature);
        evaluate();
    }

    // Re-evaluate all features to update the geometry.
    void evaluate() {
        geometry_.operations.clear();
        for (const auto &f : features_) {
            f->evaluate(geometry_);
        }
    }

    const Geometry &geometry() const { return geometry_; }

private:
    std::vector<std::shared_ptr<Feature>> features_;
    Geometry geometry_;
};

// Example usage (for compilation check only).
#ifdef HISTORY_TREE_EXAMPLE
#include <iostream>
int main() {
    HistoryTree tree;
    auto extrude = std::make_shared<ExtrudeFeature>(5.0);
    tree.addFeature(extrude);
    auto fillet = std::make_shared<FilletFeature>(1.0);
    tree.addFeature(fillet);

    // Modify parameter; tree re-evaluates automatically.
    extrude->setHeight(10.0);

    for (const auto &op : tree.geometry().operations) {
        std::cout << op << std::endl;
    }
    return 0;
}
#endif
