#include "libbbox.h"
#include "boundingbox.hpp"

inline bool check_mode(int mode){
	switch (mode)
	{
	case 0:
	case 1:
	case 2:return true;
	default:return false;
	}
}

API_PROTOCOL BBox CALL_PROTOCOL creat_bbox(){
	return static_cast<BBox>(new BoundingBox());
}

API_PROTOCOL void CALL_PROTOCOL delete_bbox(BBox bbox){
	delete static_cast<BoundingBox*>(bbox);
}

//bbox setters
API_PROTOCOL void CALL_PROTOCOL set_bbox_id(BBox bbox, int id){
	static_cast<BoundingBox*>(bbox)->set_id(id);
}

API_PROTOCOL void CALL_PROTOCOL set_bbox_label(BBox bbox, int label){
	static_cast<BoundingBox*>(bbox)->set_label(label);
}

API_PROTOCOL void CALL_PROTOCOL set_bbox_score(BBox bbox, float score){
	static_cast<BoundingBox*>(bbox)->set_score(score);
}

API_PROTOCOL void CALL_PROTOCOL set_bbox_rect(BBox bbox,
	float bbv1, float bbv2, float bbv3, float bbv4){
	static_cast<BoundingBox*>(bbox)->set_rect(bbv1, bbv2, bbv3, bbv4);
}
//BBox mode:
//0--xmin,ymin,xmax,ymax
//1--xmin,ymin,width,height
//2--xcentroid,ycentroid,width,height
API_PROTOCOL void CALL_PROTOCOL set_bbox_mode(BBox bbox, int mode){
	if (check_mode(mode))
	{
		static_cast<BoundingBox*>(bbox)->set_mode(BoundingBox::BBoxMode(mode));
	}
}

API_PROTOCOL void CALL_PROTOCOL set_bbox_normalized(BBox bbox, bool normalized){
	static_cast<BoundingBox*>(bbox)->set_normalized(normalized);
}

API_PROTOCOL void CALL_PROTOCOL set_bbox_occluded(BBox bbox, bool occluded){
	static_cast<BoundingBox*>(bbox)->set_occluded(occluded);
}

API_PROTOCOL void CALL_PROTOCOL set_bbox_truncated(BBox bbox, bool truncated){
	static_cast<BoundingBox*>(bbox)->set_truncated(truncated);
}

API_PROTOCOL void CALL_PROTOCOL set_bbox_difficult(BBox bbox, bool difficult){
	static_cast<BoundingBox*>(bbox)->set_difficult(difficult);
}

API_PROTOCOL void CALL_PROTOCOL set_bbox(BBox bbox,
	int id, int label, float score, float bbv1, float bbv2, float bbv3, float bbv4,
	int mode, bool normalized, bool occluded, bool truncated, bool difficult){
	if (check_mode(mode))
	{
		static_cast<BoundingBox*>(bbox)->set_bbox(id, label, score, bbv1, bbv2, bbv3, bbv4,
			BoundingBox::BBoxMode(mode), normalized, occluded, truncated, difficult);
	}
}
//change the rect values according to mode value
API_PROTOCOL void CALL_PROTOCOL change_bbox_mode(BBox bbox, const int mode){
	if (check_mode(mode))
	{
		static_cast<BoundingBox*>(bbox)->change_mode(BoundingBox::BBoxMode(mode));
	}
}

//change the rect values according to normalized value
API_PROTOCOL void CALL_PROTOCOL change_bbox_normalized(BBox bbox,
	const bool normalized, const float width_factor, const float height_factor){
	static_cast<BoundingBox*>(bbox)->change_normalized(normalized, 
		width_factor, height_factor);
}

//correct the rect values to [0,width_factor),[0,height_factor)
//or [0,1),[0,1)
API_PROTOCOL void CALL_PROTOCOL bbox_correct_values(
	BBox bbox, float width_factor, float height_factor){
	static_cast<BoundingBox*>(bbox)->correct_values(width_factor, height_factor);
}

API_PROTOCOL void CALL_PROTOCOL copy_bbox(const BBox src, BBox dst){
	const BoundingBox* src_bbox = static_cast<const BoundingBox*>(src);
	static_cast<BoundingBox*>(dst)->set_bbox(*src_bbox);
}

//bbox getters
API_PROTOCOL int CALL_PROTOCOL bbox_id(const BBox bbox){
	return static_cast<const BoundingBox*>(bbox)->id();
}

API_PROTOCOL int CALL_PROTOCOL bbox_label(const BBox bbox){
	return static_cast<const BoundingBox*>(bbox)->label();
}

API_PROTOCOL float CALL_PROTOCOL bbox_score(const BBox bbox){
	return static_cast<const BoundingBox*>(bbox)->score();
}

API_PROTOCOL void CALL_PROTOCOL bbox_rect(const BBox bbox,
	float* bbv1, float* bbv2, float* bbv3, float* bbv4){
	static_cast<const BoundingBox*>(bbox)->get_rect(
		bbv1, bbv2, bbv3, bbv4);
}

API_PROTOCOL int CALL_PROTOCOL bbox_mode(const BBox bbox){
	return static_cast<const BoundingBox*>(bbox)->mode();
}

API_PROTOCOL bool CALL_PROTOCOL bbox_normalized(const BBox bbox){
	return static_cast<const BoundingBox*>(bbox)->normalized();
}

API_PROTOCOL bool CALL_PROTOCOL bbox_occluded(const BBox bbox){
	return static_cast<const BoundingBox*>(bbox)->occluded();
}

API_PROTOCOL bool CALL_PROTOCOL bbox_truncated(const BBox bbox){
	return static_cast<const BoundingBox*>(bbox)->truncated();
}

API_PROTOCOL bool CALL_PROTOCOL bbox_difficult(const BBox bbox){
	return static_cast<const BoundingBox*>(bbox)->difficult();
}

//get original values
API_PROTOCOL float CALL_PROTOCOL bbox_xmin(const BBox bbox){
	return static_cast<const BoundingBox*>(bbox)->xmin();
}

API_PROTOCOL float CALL_PROTOCOL bbox_ymin(const BBox bbox){
	return static_cast<const BoundingBox*>(bbox)->ymin();
}

API_PROTOCOL float CALL_PROTOCOL bbox_xmax(const BBox bbox){
	return static_cast<const BoundingBox*>(bbox)->xmax();
}

API_PROTOCOL float CALL_PROTOCOL bbox_ymax(const BBox bbox){
	return static_cast<const BoundingBox*>(bbox)->ymax();
}

API_PROTOCOL float CALL_PROTOCOL bbox_xcentroid(const BBox bbox){
	return static_cast<const BoundingBox*>(bbox)->xcentroid();
}

API_PROTOCOL float CALL_PROTOCOL bbox_ycentroid(const BBox bbox){
	return static_cast<const BoundingBox*>(bbox)->ycentroid();
}

API_PROTOCOL float CALL_PROTOCOL bbox_width(const BBox bbox){
	return static_cast<const BoundingBox*>(bbox)->width();
}

API_PROTOCOL float CALL_PROTOCOL bbox_height(const BBox bbox){
	return static_cast<const BoundingBox*>(bbox)->height();
}

API_PROTOCOL float CALL_PROTOCOL bbox_area(const BBox bbox){
	return static_cast<const BoundingBox*>(bbox)->area();
}
//get normalized values
//the width_factor or/and height_factor must be given in case the bbox is unnormalized
API_PROTOCOL float CALL_PROTOCOL bbox_normalized_xmin(const BBox bbox, float factor){
	return static_cast<const BoundingBox*>(bbox)->normalized_xmin(factor);
}

API_PROTOCOL float CALL_PROTOCOL bbox_normalized_ymin(const BBox bbox, float factor){
	return static_cast<const BoundingBox*>(bbox)->normalized_ymin(factor);
}

API_PROTOCOL float CALL_PROTOCOL bbox_normalized_xmax(const BBox bbox, float factor){
	return static_cast<const BoundingBox*>(bbox)->normalized_xmax(factor);
}

API_PROTOCOL float CALL_PROTOCOL bbox_normalized_ymax(const BBox bbox, float factor){
	return static_cast<const BoundingBox*>(bbox)->normalized_ymax(factor);
}

API_PROTOCOL float CALL_PROTOCOL bbox_normalized_xcentroid(const BBox bbox, float factor){
	return static_cast<const BoundingBox*>(bbox)->normalized_xcentroid(factor);
}

API_PROTOCOL float CALL_PROTOCOL bbox_normalized_ycentroid(const BBox bbox, float factor){
	return static_cast<const BoundingBox*>(bbox)->normalized_ycentroid(factor);
}

API_PROTOCOL float CALL_PROTOCOL bbox_normalized_width(const BBox bbox, float factor){
	return static_cast<const BoundingBox*>(bbox)->normalized_width(factor);
}

API_PROTOCOL float CALL_PROTOCOL bbox_normalized_height(const BBox bbox, float factor){
	return static_cast<const BoundingBox*>(bbox)->normalized_height(factor);
}

API_PROTOCOL float CALL_PROTOCOL bbox_normalized_area(
	const BBox bbox, float width_factor, float height_factor){
	return static_cast<const BoundingBox*>(bbox)->normalized_area(
		width_factor, height_factor);
}
//get unnormalized values
//the width_factor or/and height_factor must be given in case the bbox is normalized
API_PROTOCOL float CALL_PROTOCOL bbox_unnormalized_xmin(const BBox bbox, float factor){
	return static_cast<const BoundingBox*>(bbox)->unnormalized_xmin(factor);
}

API_PROTOCOL float CALL_PROTOCOL bbox_unnormalized_ymin(const BBox bbox, float factor){
	return static_cast<const BoundingBox*>(bbox)->unnormalized_ymin(factor);
}

API_PROTOCOL float CALL_PROTOCOL bbox_unnormalized_xmax(const BBox bbox, float factor){
	return static_cast<const BoundingBox*>(bbox)->unnormalized_xmax(factor);
}

API_PROTOCOL float CALL_PROTOCOL bbox_unnormalized_ymax(const BBox bbox, float factor){
	return static_cast<const BoundingBox*>(bbox)->unnormalized_ymax(factor);
}

API_PROTOCOL float CALL_PROTOCOL bbox_unnormalized_xcentroid(const BBox bbox, float factor){
	return static_cast<const BoundingBox*>(bbox)->unnormalized_xcentroid(factor);
}

API_PROTOCOL float CALL_PROTOCOL bbox_unnormalized_ycentroid(const BBox bbox, float factor){
	return static_cast<const BoundingBox*>(bbox)->unnormalized_ycentroid(factor);
}

API_PROTOCOL float CALL_PROTOCOL bbox_unnormalized_width(const BBox bbox, float factor){
	return static_cast<const BoundingBox*>(bbox)->unnormalized_width(factor);
}

API_PROTOCOL float CALL_PROTOCOL bbox_unnormalized_height(const BBox bbox, float factor){
	return static_cast<const BoundingBox*>(bbox)->unnormalized_height(factor);
}

API_PROTOCOL float CALL_PROTOCOL bbox_unnormalized_area(
	const BBox bbox, float width_factor, float height_factor){
	return static_cast<const BoundingBox*>(bbox)->unnormalized_area(
		width_factor, height_factor);
}
//get the iou overlap
//return -1 if the normalized setting is different
API_PROTOCOL float CALL_PROTOCOL bboxes_overlap(
	const BBox bbox1, const BBox bbox2, bool inclass){
	const BoundingBox* bb2 = static_cast<const BoundingBox*>(bbox2);
	return static_cast<const BoundingBox*>(bbox1)->overlap(*bb2, inclass);
}
//Returns true if the bbox2 is inside bbox1.
//otherwise returns false.
//If proper is true, this function only returns true 
//if the rectangle is entirely inside this rectangle(not on the edge).
//return false if the normalized not equal
API_PROTOCOL bool CALL_PROTOCOL bbox_contain_bbox(
	const BBox bbox1, const BBox bbox2, bool proper){
	const BoundingBox* bb2 = static_cast<const BoundingBox*>(bbox2);
	return static_cast<const BoundingBox*>(bbox1)->contain(*bb2, proper);
}
//Returns true if the point (x, y) is inside or on the edge of the rectangle, 
//otherwise returns false. 
//If proper is true, this function only returns true 
//if the point is entirely inside the rectangle(not on the edge).
//return false if the normalized not equal
API_PROTOCOL bool CALL_PROTOCOL bbox_contain_point(const BBox bbox,
	float x, float y, bool normalized, bool proper){
	return static_cast<const BoundingBox*>(bbox)->contain(x, y, normalized, proper);
}