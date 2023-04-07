#include "Region.h"

using namespace psdf;

Region::Region()
    : mBounds({{-kInitialBoundScale, -kInitialBoundScale},
               {kInitialBoundScale, -kInitialBoundScale},
               {kInitialBoundScale, kInitialBoundScale},
               {-kInitialBoundScale, kInitialBoundScale}})
{
}

Region::Region(std::vector<glm::dvec2> bounds) : mBounds(std::move(bounds))
{
}

std::vector<glm::dvec2> Region::getBounds() const
{
    return mBounds;
}

void Region::polyCut(const std::vector<Point> &points, const std::vector<glm::dvec2> &edgeVectors)
{
    if (mBounds.empty())
    {
        return;
    }
    for (size_t i = 0; i < points.size(); i++)
    {
        double d = glm::dot(points[i], edgeVectors[i]);
        std::vector<double> vnd = calculateVnd(edgeVectors[i], d);
        std::vector<bool> b(vnd.size());
        std::transform(vnd.cbegin(), vnd.cend(), b.begin(), [](double v) { return v <= 0; });
        if (std::all_of(b.cbegin(), b.cend(), [](bool p) { return p; }))
        {
            continue;
        }
        else if (!std::any_of(b.cbegin(), b.cend(), [](bool p) { return p; }))
        {
            mBounds.clear();
            return;
        }
        calculateNewBounds(vnd, b);
    }
}

std::vector<double> Region::calculateVnd(glm::dvec2 edgeVector, double d)
{
    std::vector<double> vnd(mBounds.size());
    for (size_t i = 0; i < vnd.size(); ++i)
    {
        vnd[i] = glm::dot(mBounds[i], edgeVector) - d;
    }
    return vnd;
}

void Region::calculateNewBounds(const std::vector<double> &vnd, std::vector<bool> &b)
{
    std::vector<int> ind = getNeighborDifference(b);
    int64_t m1 = std::distance(ind.cbegin(), std::find(ind.cbegin(), ind.cend(), -1));
    size_t m0 = (m1 + (ind.size() - 1)) % ind.size();

    int64_t p1 = std::distance(ind.cbegin(), std::find(ind.cbegin(), ind.cend(), 1));
    size_t p0 = (p1 + (ind.size() - 1)) % ind.size();

    glm::dvec2 vndSlice0{vnd[m0], vnd[p0]};
    glm::dvec2 vndSlice1{vnd[m1], vnd[p1]};
    glm::dvec2 tt = 1.0 - vndSlice1 / (vndSlice1 - vndSlice0);

    std::vector<glm::dvec2> w{mBounds[m0] * (1.0f - tt[0]) + mBounds[m1] * tt[0],
                              mBounds[p0] * (1.0f - tt[1]) + mBounds[p1] * tt[1]};
    applyNewBounds(b, w, m0, p1);
}

std::vector<int> Region::getNeighborDifference(const std::vector<bool> &b)
{
    std::vector<int> ind(b.size());
    for (size_t i = 0; i < b.size(); i++)
    {
        bool b1 = b[(i + b.size() - 1) % b.size()];
        bool b2 = b[i];
        ind[i] = b1 - b2;
    }
    return ind;
}

void Region::applyNewBounds(std::vector<bool> &b, const std::vector<glm::dvec2> &w, size_t m0, size_t p1)
{
    std::vector<glm::dvec2> newBounds;
    newBounds.reserve(mBounds.size());
    if (m0 == p1)
    {
        FALCOR_ASSERT(m0 >= 0);
        mBounds.emplace_back(0.0f); // in this case we extend the bounding polygon by one vertex
        for (size_t i = mBounds.size() - 1; i >= m0 + 2; i--)
        {
            mBounds[i] = mBounds[i - 1];
        }
        mBounds[m0] = w[1];
        mBounds[m0 + 1] = w[0];
    }
    else
    {
        mBounds[m0] = w[0];
        mBounds[p1] = w[1];
        b[m0] = true;
        b[p1] = true;
        std::vector<glm::dvec2> newBounds;
        newBounds.reserve(mBounds.size());
        for (size_t i = 0; i < b.size(); i++)
        {
            if (b[i])
            {
                newBounds.emplace_back(mBounds[i]);
            }
        }
        mBounds = newBounds;
    }
}
