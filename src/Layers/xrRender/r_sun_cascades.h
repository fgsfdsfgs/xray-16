#pragma once

namespace sun
{
struct ray
{
    ray() {}
    ray(Fvector3 const& _PP, Fvector3 const& _D) : D(_D), P(_PP) {}
    Fvector3 D;
    Fvector3 P;
};

struct cascade
{
    cascade() : reset_chain(false) {}
    Fmatrix xform;
    xr_vector<ray> rays;
    float size;
    float bias;
    bool reset_chain;
};

} // namespace sun
