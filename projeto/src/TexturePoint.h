#ifndef TEXTUREPOINT_H
#define TEXTUREPOINT_H

class TexturePoint
{
private:
    float u, v;
public:
    TexturePoint();
    TexturePoint(float _u, float _v);
    TexturePoint(const TexturePoint& p);

    float U() const;
    float V() const;

    void U(float _u);
    void V(float _v);

    const TexturePoint& operator=(const TexturePoint& p);

};

#endif // TEXTUREPOINT_H
