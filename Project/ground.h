 
class Ground {
public:
	Ground();
	Ground(const int w, const int h) :Width(w), Height(h) {};
	void draw(unsigned int texture) const;
private:
	int Width;
	int Height;
};