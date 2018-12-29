#ifndef _LIB_BBOX_H_
#define _LIB_BBOX_H_

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

//define BBox type as void*
typedef void* BBox;

API_PROTOCOL BBox CALL_PROTOCOL creat_bbox();
API_PROTOCOL void CALL_PROTOCOL delete_bbox(BBox bbox);
//bbox setters
API_PROTOCOL void CALL_PROTOCOL set_bbox_id(BBox bbox, int id);
API_PROTOCOL void CALL_PROTOCOL set_bbox_label(BBox bbox, int label);
API_PROTOCOL void CALL_PROTOCOL set_bbox_score(BBox bbox, float score);
API_PROTOCOL void CALL_PROTOCOL set_bbox_rect(BBox bbox,
	float bbv1, float bbv2, float bbv3, float bbv4);
//BBox mode:
//0--xmin,ymin,xmax,ymax
//1--xmin,ymin,width,height
//2--xcentroid,ycentroid,width,height
API_PROTOCOL void CALL_PROTOCOL set_bbox_mode(BBox bbox, int mode);
API_PROTOCOL void CALL_PROTOCOL set_bbox_normalized(BBox bbox, bool normalized);
API_PROTOCOL void CALL_PROTOCOL set_bbox_occluded(BBox bbox, bool occluded);
API_PROTOCOL void CALL_PROTOCOL set_bbox_truncated(BBox bbox, bool truncated);
API_PROTOCOL void CALL_PROTOCOL set_bbox_difficult(BBox bbox, bool difficult);
API_PROTOCOL void CALL_PROTOCOL set_bbox(BBox bbox,
	int id, int label, float score, float bbv1, float bbv2, float bbv3, float bbv4,
	int mode, bool normalized, bool occluded, bool truncated, bool difficult);
//change the rect values according to mode value
API_PROTOCOL void CALL_PROTOCOL change_bbox_mode(BBox bbox, const int mode);
//change the rect values according to normalized value
API_PROTOCOL void CALL_PROTOCOL change_bbox_normalized(BBox bbox,
	const bool normalized, const float width_factor, const float height_factor);
//correct the rect values to [0,width_factor),[0,height_factor)
//or [0,1),[0,1)
API_PROTOCOL void CALL_PROTOCOL bbox_correct_values(
	BBox bbox, float width_factor, float height_factor);
API_PROTOCOL void CALL_PROTOCOL copy_bbox(const BBox src, BBox dst);
//bbox getters
API_PROTOCOL int CALL_PROTOCOL bbox_id(const BBox bbox);
API_PROTOCOL int CALL_PROTOCOL bbox_label(const BBox bbox);
API_PROTOCOL float CALL_PROTOCOL bbox_score(const BBox bbox);
API_PROTOCOL void CALL_PROTOCOL bbox_rect(const BBox bbox,
	float* bbv1, float* bbv2, float* bbv3, float* bbv4);
API_PROTOCOL int CALL_PROTOCOL bbox_mode(const BBox bbox);
API_PROTOCOL bool CALL_PROTOCOL bbox_normalized(const BBox bbox);
API_PROTOCOL bool CALL_PROTOCOL bbox_occluded(const BBox bbox);
API_PROTOCOL bool CALL_PROTOCOL bbox_truncated(const BBox bbox);
API_PROTOCOL bool CALL_PROTOCOL bbox_difficult(const BBox bbox);
//get original values
API_PROTOCOL float CALL_PROTOCOL bbox_xmin(const BBox bbox);
API_PROTOCOL float CALL_PROTOCOL bbox_ymin(const BBox bbox);
API_PROTOCOL float CALL_PROTOCOL bbox_xmax(const BBox bbox);
API_PROTOCOL float CALL_PROTOCOL bbox_ymax(const BBox bbox);
API_PROTOCOL float CALL_PROTOCOL bbox_xcentroid(const BBox bbox);
API_PROTOCOL float CALL_PROTOCOL bbox_ycentroid(const BBox bbox);
API_PROTOCOL float CALL_PROTOCOL bbox_width(const BBox bbox);
API_PROTOCOL float CALL_PROTOCOL bbox_height(const BBox bbox);
API_PROTOCOL float CALL_PROTOCOL bbox_area(const BBox bbox);
//get normalized values
//the width_factor or/and height_factor must be given in case the bbox is unnormalized
API_PROTOCOL float CALL_PROTOCOL bbox_normalized_xmin(const BBox bbox, float factor);
API_PROTOCOL float CALL_PROTOCOL bbox_normalized_ymin(const BBox bbox, float factor);
API_PROTOCOL float CALL_PROTOCOL bbox_normalized_xmax(const BBox bbox, float factor);
API_PROTOCOL float CALL_PROTOCOL bbox_normalized_ymax(const BBox bbox, float factor);
API_PROTOCOL float CALL_PROTOCOL bbox_normalized_xcentroid(const BBox bbox, float factor);
API_PROTOCOL float CALL_PROTOCOL bbox_normalized_ycentroid(const BBox bbox, float factor);
API_PROTOCOL float CALL_PROTOCOL bbox_normalized_width(const BBox bbox, float factor);
API_PROTOCOL float CALL_PROTOCOL bbox_normalized_height(const BBox bbox, float factor);
API_PROTOCOL float CALL_PROTOCOL bbox_normalized_area(
	const BBox bbox, float width_factor, float height_factor);
//get unnormalized values
//the width_factor or/and height_factor must be given in case the bbox is normalized
API_PROTOCOL float CALL_PROTOCOL bbox_unnormalized_xmin(const BBox bbox, float factor);
API_PROTOCOL float CALL_PROTOCOL bbox_unnormalized_ymin(const BBox bbox, float factor);
API_PROTOCOL float CALL_PROTOCOL bbox_unnormalized_xmax(const BBox bbox, float factor);
API_PROTOCOL float CALL_PROTOCOL bbox_unnormalized_ymax(const BBox bbox, float factor);
API_PROTOCOL float CALL_PROTOCOL bbox_unnormalized_xcentroid(const BBox bbox, float factor);
API_PROTOCOL float CALL_PROTOCOL bbox_unnormalized_ycentroid(const BBox bbox, float factor);
API_PROTOCOL float CALL_PROTOCOL bbox_unnormalized_width(const BBox bbox, float factor);
API_PROTOCOL float CALL_PROTOCOL bbox_unnormalized_height(const BBox bbox, float factor);
API_PROTOCOL float CALL_PROTOCOL bbox_unnormalized_area(
	const BBox bbox, float width_factor, float height_factor);
//get the iou overlap
//return -1 if the normalized setting is different
API_PROTOCOL float CALL_PROTOCOL bboxes_overlap(
	const BBox bbox1, const BBox bbox2, bool inclass);
//Returns true if the bbox2 is inside bbox1.
//otherwise returns false.
//If proper is true, this function only returns true 
//if the rectangle is entirely inside this rectangle(not on the edge).
//return false if the normalized not equal
API_PROTOCOL bool CALL_PROTOCOL bbox_contain_bbox(
	const BBox bbox1, const BBox bbox2, bool proper);
//Returns true if the point (x, y) is inside or on the edge of the rectangle, 
//otherwise returns false. 
//If proper is true, this function only returns true 
//if the point is entirely inside the rectangle(not on the edge).
//return false if the normalized not equal
API_PROTOCOL bool CALL_PROTOCOL bbox_contain_point(const BBox bbox,
	float x, float y, bool normalized, bool proper);

#endif // !_LIB_BBOX_H_
