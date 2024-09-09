struct Vector2 {
 public:
    Vector2(void);
    Vector2(float x, float y);
    ~Vector2(void);
    Vector2(Vector2 const& rhs);
    Vector2& operator=(Vector2 const& rhs);

    float getX() const;
    float getY() const;
    void setX(float x);
    void setY(float x);

 private:
    float _x;
    float _y;
};
