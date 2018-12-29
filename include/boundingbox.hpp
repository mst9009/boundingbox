//************FOR CPP STYLE******************//
#ifndef _BOUNDINGBOX_CPP_HPP_
#define _BOUNDINGBOX_CPP_HPP_

#ifndef EXTERN_C
#ifdef __cplusplus
#define EXTERN_C extern "C"
#else
#define EXTERN_C
#endif // __cplusplus
#endif // !EXTERN_C

#ifndef DLL_PROTOCOL
#ifdef _MSC_VER
#ifdef DLL_EXPORT
#define DLL_PROTOCOL _declspec(dllexport)
#else
#define DLL_PROTOCOL _declspec(dllimport)
#endif // DLL_EXPORT
#else
#define DLL_PROTOCOL
#endif // _MSC_VER
#endif // !DLL_PROTOCOL

#ifndef API_PROTOCOL
#define API_PROTOCOL EXTERN_C DLL_PROTOCOL
#endif // !API_PROTOCOL

#ifndef CALL_PROTOCOL
#ifdef _MSC_VER
#define CALL_PROTOCOL __stdcall
#else
#define CALL_PROTOCOL __attribute__((stdcall))
#endif // _MSC_VER
#endif // !CALL_PROTOCOL

class DLL_PROTOCOL BoundingBox
{
public:

	enum BBoxMode
	{
		CORNER_CORNER = 0,			//xmin,ymin,xmax,ymax
		CORNER_SIZE = 1,			//xmin,ymin,width,height
		CENTROID_SIZE = 2			//xcentroid,ycentroid,width,height
	};

	BoundingBox() = default;
	BoundingBox(float bbv1, float bbv2, float bbv3, float bbv4,
		BoundingBox::BBoxMode mode = BoundingBox::CORNER_CORNER, bool normalized = true){
		set_bbox(0, 0, 1, bbv1, bbv2, bbv3, bbv4, mode, 
			normalized, false, false, false);
	}
	BoundingBox(int label, float score, float bbv1, float bbv2, float bbv3, float bbv4,
		BoundingBox::BBoxMode mode = BoundingBox::CORNER_CORNER, bool normalized = true,
		bool occluded = false, bool truncated = false, bool difficult = false) {
		set_bbox(0, label, score, bbv1, bbv2, bbv3, bbv4, mode,
			normalized, occluded, truncated, difficult);
	}
	BoundingBox(int id, int label, float score, float bbv1, float bbv2, float bbv3, float bbv4,
		BoundingBox::BBoxMode mode = BoundingBox::CORNER_CORNER, bool normalized = true,
		bool occluded = false, bool truncated = false, bool difficult = false) {
		set_bbox(id, label, score, bbv1, bbv2, bbv3, bbv4, mode,
			normalized, occluded, truncated, difficult);
	}
	BoundingBox(const BoundingBox& bbox){ set_bbox(bbox); }
	~BoundingBox() = default;
	void set_id(int id){ id_ = id; }
	void set_label(int label){ label_ = label; }
	void set_score(float score){ score_ = score; }
	void set_rect(float bbv1, float bbv2, float bbv3, float bbv4){
		bbv1_ = bbv1;
		bbv2_ = bbv2;
		bbv3_ = bbv3;
		bbv4_ = bbv4;
	}
	//only change bbox mode,keep the rect values
	void set_mode(BoundingBox::BBoxMode mode){ mode_ = mode; }
	//only change normalized attribute,keep the rect values
	void set_normalized(bool normalized){ normalized_ = normalized; }
	void set_occluded(bool occluded){ occluded_ = occluded; }
	void set_truncated(bool truncated){ truncated_ = truncated; }
	void set_difficult(bool difficult){ difficult_ = difficult; }
	void set_bbox(int id, int label, float score, float bbv1, float bbv2, float bbv3, float bbv4,
		BoundingBox::BBoxMode mode = BoundingBox::CORNER_CORNER, bool normalized = true,
		bool occluded = false, bool truncated = false, bool difficult = false){
		id_ = id;
		label_ = label;
		score_ = score;
		bbv1_ = bbv1;
		bbv2_ = bbv2;
		bbv3_ = bbv3;
		bbv4_ = bbv4;
		mode_ = mode;
		normalized_ = normalized;
		occluded_ = occluded;
		truncated_ = truncated;
		difficult_ = difficult;
	}
	void set_bbox(const BoundingBox& bbox){
		id_ = bbox.id();
		label_ = bbox.label();
		score_ = bbox.score();
		bbox.get_rect(&bbv1_, &bbv2_, &bbv3_, &bbv4_);
		mode_ = bbox.mode();
		normalized_ = bbox.normalized();
		occluded_ = bbox.occluded();
		truncated_ = bbox.truncated();
		difficult_ = bbox.difficult();
	}
	void get_rect(float* bbv1, float* bbv2, float* bbv3, float* bbv4) const {
		*bbv1 = bbv1_;
		*bbv2 = bbv2_;
		*bbv3 = bbv3_;
		*bbv4 = bbv4_;
	}
	BoundingBox& operator=(const BoundingBox& bbox){
		this->set_bbox(bbox);
		return *this;
	}
	//change the rect values according to mode value
	void change_mode(const BoundingBox::BBoxMode mode);
	//change the rect values according to normalized value
	void change_normalized(const bool normalized, 
		const float width_factor, const float height_factor);

	int id() const { return id_; }
	int label() const{ return label_; }
	float score() const{ return score_; }
	BoundingBox::BBoxMode mode() const{ return mode_; }
	bool normalized() const { return normalized_; }
	bool occluded() const { return occluded_; }
	bool truncated() const { return truncated_; }
	bool difficult() const { return difficult_; }
	
	float xmin() const;
	float ymin() const;
	float xmax() const;
	float ymax() const;
	float xcentroid() const;
	float ycentroid() const;
	float width() const;
	float height() const;
	float area() const;

	float normalized_xmin(const float factor) const;
	float normalized_ymin(const float factor) const;
	float normalized_xmax(const float factor) const;
	float normalized_ymax(const float factor) const;
	float normalized_xcentroid(const float factor) const;
	float normalized_ycentroid(const float factor) const;
	float normalized_width(const float factor) const;
	float normalized_height(const float factor) const;
	float normalized_area(
		const float width_factor, const float height_factor) const;

	float unnormalized_xmin(const float factor) const;
	float unnormalized_ymin(const float factor) const;
	float unnormalized_xmax(const float factor) const;
	float unnormalized_ymax(const float factor) const;
	float unnormalized_xcentroid(const float factor) const;
	float unnormalized_ycentroid(const float factor) const;
	float unnormalized_width(const float factor) const;
	float unnormalized_height(const float factor) const;
	float unnormalized_area(
		const float width_factor, const float height_factor) const;
	//get the iou overlap
	//return -1 if the normalized setting is different
	float overlap(const BoundingBox& bbox, const bool inclass = true) const;
	//correct the rect values to [0,width_factor),[0,height_factor)
	//or [0,1),[0,1)
	void correct_values(
		const float width_factor, const float height_factor);
	//Returns true if the given rectangle is inside this rectangle.
	//otherwise returns false.
	//If proper is true, this function only returns true 
	//if the rectangle is entirely inside this rectangle(not on the edge).
	//return false if the normalized not equal
	bool contain(const BoundingBox& bbox, bool proper) const;
	//Returns true if the point (x, y) is inside or on the edge of the rectangle, 
	//otherwise returns false. 
	//If proper is true, this function only returns true 
	//if the point is entirely inside the rectangle(not on the edge).
	//return false if the normalized not equal
	bool contain(float x, float y, bool normalized, bool proper) const;
	
private:
	int id_;
	int label_;
	float score_;
	float bbv1_, bbv2_, bbv3_, bbv4_;
	BoundingBox::BBoxMode mode_;
	bool normalized_;
	bool occluded_;
	bool truncated_;
	bool difficult_;
};
//common version for overlap function
API_PROTOCOL float CALL_PROTOCOL bboxes_overlap(const BoundingBox& bbox1,
	const BoundingBox& bbox2, const bool inclass = true);
#endif // !_BOUNDINGBOX_CPP_HPP_
