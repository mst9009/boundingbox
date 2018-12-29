#include "boundingbox.hpp"
#include <algorithm>

void BoundingBox::change_mode(const BoundingBox::BBoxMode mode){
	if (mode == mode_)return;
	switch (mode)
	{
	case BoundingBox::CORNER_CORNER:
		this->set_rect(this->xmin(), this->ymin(), this->xmax(), this->ymax());
		break;
	case BoundingBox::CORNER_SIZE:
		this->set_rect(this->xmin(), this->ymin(), this->width(), this->height());
		break;
	case BoundingBox::CENTROID_SIZE:
		this->set_rect(this->xcentroid(), this->ycentroid(), this->width(), this->height());
		break;
	default:
		break;
	}
	this->set_mode(mode);
}

void BoundingBox::change_normalized(const bool normalized, 
	const float width_factor, const float height_factor){
	if (width_factor <= 1 || height_factor <= 1)return;
	if (normalized == normalized_)return;
	if (normalized)
	{
		//unnormalized ==> normalized
		bbv1_ /= width_factor;
		bbv2_ /= height_factor;
		bbv3_ /= width_factor;
		bbv4_ /= height_factor;
	}
	else
	{
		bbv1_ *= width_factor;
		bbv2_ *= height_factor;
		bbv3_ *= width_factor;
		bbv4_ *= height_factor;
	}
	normalized_ = normalized;
}

float BoundingBox::xmin() const {
	switch (mode_)
	{
	case BoundingBox::CORNER_CORNER:
		return bbv1_;
	case BoundingBox::CORNER_SIZE:
		return bbv1_;
	case BoundingBox::CENTROID_SIZE:
		return normalized_ ? (bbv1_ - bbv3_ / 2) : (bbv1_ - (bbv3_ - 1) / 2);
	default:
		return -1;
	}
}

float BoundingBox::ymin() const {
	switch (mode_)
	{
	case BoundingBox::CORNER_CORNER:
		return bbv2_;
	case BoundingBox::CORNER_SIZE:
		return bbv2_;
	case BoundingBox::CENTROID_SIZE:
		return normalized_ ? (bbv2_ - bbv4_ / 2) : (bbv2_ - (bbv4_ - 1) / 2);
	default:
		return -1;
	}
}

float BoundingBox::xmax() const {
	switch (mode_)
	{
	case BoundingBox::CORNER_CORNER:
		return bbv3_;
	case BoundingBox::CORNER_SIZE:
		return normalized_ ? (bbv1_ + bbv3_) : (bbv1_ + bbv3_ - 1);
	case BoundingBox::CENTROID_SIZE:
		return normalized_ ? (bbv1_ + bbv3_ / 2) : (bbv1_ + (bbv3_ - 1) / 2);
	default:
		return -1;
	}
}

float BoundingBox::ymax() const {
	switch (mode_)
	{
	case BoundingBox::CORNER_CORNER:
		return bbv4_;
	case BoundingBox::CORNER_SIZE:
		return normalized_ ? (bbv2_ + bbv4_) : (bbv2_ + bbv4_ - 1);
	case BoundingBox::CENTROID_SIZE:
		return normalized_ ? (bbv2_ + bbv4_ / 2) : (bbv2_ + (bbv4_ - 1) / 2);
	default:
		return -1;
	}
}

float BoundingBox::xcentroid() const {
	switch (mode_)
	{
	case BoundingBox::CORNER_CORNER:
		return (bbv1_ + bbv3_) / 2;
	case BoundingBox::CORNER_SIZE:
		return normalized_ ? (bbv1_ + bbv3_ / 2) : (bbv1_ + (bbv3_ - 1) / 2);
	case BoundingBox::CENTROID_SIZE:
		return bbv1_;
	default:
		return -1;
	}
}

float BoundingBox::ycentroid() const {
	switch (mode_)
	{
	case BoundingBox::CORNER_CORNER:
		return (bbv2_ + bbv4_) / 2;
	case BoundingBox::CORNER_SIZE:
		return normalized_ ? (bbv2_ + bbv4_ / 2) : (bbv2_ + (bbv4_ - 1) / 2);
	case BoundingBox::CENTROID_SIZE:
		return bbv2_;
	default:
		return -1;
	}
}

float BoundingBox::width() const {
	switch (mode_)
	{
	case BoundingBox::CORNER_CORNER:
		return normalized_ ? (bbv3_ - bbv1_) : (bbv3_ - bbv1_ + 1);
	case BoundingBox::CORNER_SIZE:
		return bbv3_;
	case BoundingBox::CENTROID_SIZE:
		return bbv3_;
	default:
		return -1;
	}
}

float BoundingBox::height() const {
	switch (mode_)
	{
	case BoundingBox::CORNER_CORNER:
		return normalized_ ? (bbv4_ - bbv2_) : (bbv4_ - bbv2_ + 1);
	case BoundingBox::CORNER_SIZE:
		return bbv4_;
	case BoundingBox::CENTROID_SIZE:
		return bbv4_;
	default:
		return -1;
	}
}

float BoundingBox::area() const {
	switch (mode_)
	{
	case BoundingBox::CORNER_CORNER:
		return normalized_ ?
			((bbv3_ - bbv1_)*(bbv4_ - bbv2_)) :
			((bbv3_ - bbv1_ + 1)*(bbv4_ - bbv2_ + 1));
	case BoundingBox::CORNER_SIZE:
		return bbv3_*bbv4_;
	case BoundingBox::CENTROID_SIZE:
		return bbv3_*bbv4_;
	default:
		return -1;
	}
}

float BoundingBox::normalized_xmin(const float factor) const {
	float xmin = this->xmin();
	return normalized_ ? xmin : ((factor > 1) ? (xmin / factor) : xmin);
}

float BoundingBox::normalized_ymin(const float factor) const {
	float ymin = this->ymin();
	return normalized_ ? ymin : ((factor > 1) ? (ymin / factor) : ymin);
}

float BoundingBox::normalized_xmax(const float factor) const {
	float xmax = this->xmax();
	return normalized_ ? xmax : ((factor > 1) ? (xmax / factor) : xmax);
}

float BoundingBox::normalized_ymax(const float factor) const {
	float ymax = this->ymax();
	return normalized_ ? ymax : ((factor > 1) ? (ymax / factor) : ymax);
}

float BoundingBox::normalized_xcentroid(const float factor) const {
	float xcentroid = this->xcentroid();
	return normalized_ ? xcentroid : ((factor > 1) ? (xcentroid / factor) : xcentroid);
}

float BoundingBox::normalized_ycentroid(const float factor) const {
	float ycentroid = this->ycentroid();
	return normalized_ ? ycentroid : ((factor > 1) ? (ycentroid / factor) : ycentroid);
}

float BoundingBox::normalized_width(const float factor) const {
	float width = this->width();
	return normalized_ ? width : ((factor > 1) ? (width / factor) : width);
}

float BoundingBox::normalized_height(const float factor) const {
	float height = this->height();
	return normalized_ ? height : ((factor > 1) ? (height / factor) : height);
}

float BoundingBox::normalized_area(
	const float width_factor, const float height_factor) const {
	float area = this->area();
	return normalized_ ? area : ((width_factor <= 1 || height_factor <= 1) ? area :
		(area / (width_factor*height_factor)));
}

float BoundingBox::unnormalized_xmin(const float factor) const {
	float xmin = this->xmin();
	return normalized_ ? ((factor > 1) ? (xmin*factor) : xmin) : xmin;
}

float BoundingBox::unnormalized_ymin(const float factor) const {
	float ymin = this->ymin();
	return normalized_ ? ((factor > 1) ? (ymin*factor) : ymin) : ymin;
}

float BoundingBox::unnormalized_xmax(const float factor) const {
	float xmax = this->xmax();
	return normalized_ ? ((factor > 1) ? (xmax*factor) : xmax) : xmax;
}

float BoundingBox::unnormalized_ymax(const float factor) const {
	float ymax = this->ymax();
	return normalized_ ? ((factor > 1) ? (ymax*factor) : ymax) : ymax;
}

float BoundingBox::unnormalized_xcentroid(const float factor) const {
	float xcentroid = this->xcentroid();
	return normalized_ ? ((factor > 1) ? (xcentroid*factor) : xcentroid) : xcentroid;
}

float BoundingBox::unnormalized_ycentroid(const float factor) const {
	float ycentroid = this->ycentroid();
	return normalized_ ? ((factor > 1) ? (ycentroid*factor) : ycentroid) : ycentroid;
}

float BoundingBox::unnormalized_width(const float factor) const {
	float width = this->width();
	return normalized_ ? ((factor > 1) ? (width*factor) : width) : width;
}

float BoundingBox::unnormalized_height(const float factor) const {
	float height = this->height();
	return normalized_ ? ((factor > 1) ? (height*factor) : height) : height;
}

float BoundingBox::unnormalized_area(
	const float width_factor, const float height_factor) const {
	float area = this->area();
	return normalized_ ? ((width_factor <= 1 || height_factor <= 1) ? area :
		(area * (width_factor*height_factor))) : area;
}

float BoundingBox::overlap(const BoundingBox& bbox, const bool inclass/* = true*/) const
{
	if (normalized_ != bbox.normalized())return -1;
	if (inclass && (this->label() != bbox.label()))return 0;
	float overlap_xmin = std::max(this->xmin(), bbox.xmin());
	float overlap_ymin = std::max(this->ymin(), bbox.ymin());
	float overlap_xmax = std::min(this->xmax(), bbox.xmax());
	float overlap_ymax = std::min(this->ymax(), bbox.ymax());
	if (overlap_xmin >= overlap_xmax || overlap_ymin >= overlap_ymax)return 0;
	float overlap_area = normalized_ ?
		((overlap_xmax - overlap_xmin)*(overlap_ymax - overlap_ymin)) :
		((overlap_xmax - overlap_xmin + 1)*(overlap_ymax - overlap_ymin + 1));
	return (overlap_area / (this->area() + bbox.area() - overlap_area));
}

void BoundingBox::correct_values(
	const float width_factor, const float height_factor) {
	if (width_factor <= 1 || height_factor <= 1)return;
	BoundingBox::BBoxMode ori_mode = this->mode();
	bool ori_normalized = this->normalized();
	float xmin = this->xmin();
	float ymin = this->ymin();
	float xmax = this->xmax();
	float ymax = this->ymax();
	if (ori_normalized)
	{
		xmin *= width_factor;
		ymin *= height_factor;
		xmax *= width_factor;
		ymax *= height_factor;
	}
	xmin = std::min<float>(std::max<float>(0, xmin), width_factor - 1);
	ymin = std::min<float>(std::max<float>(0, ymin), height_factor - 1);
	xmax = std::min<float>(std::max<float>(xmin, xmax), width_factor - 1);
	ymax = std::min<float>(std::max<float>(ymin, ymax), height_factor - 1);
	bbv1_ = xmin;
	bbv2_ = ymin;
	bbv3_ = xmax;
	bbv4_ = ymax;
	mode_ = BoundingBox::CORNER_CORNER;
	normalized_ = false;
	this->change_normalized(ori_normalized, width_factor, height_factor);
	this->change_mode(ori_mode);
}

bool BoundingBox::contain(const BoundingBox& bbox, bool proper) const {
	if (this->normalized() != bbox.normalized())return false;
	if (proper)
	{
		return (this->xmin() < bbox.xmin()) &&
			(this->ymin() < bbox.ymin()) &&
			(this->xmax() > bbox.xmax()) &&
			(this->ymax() > bbox.ymax());
	}
	else
	{
		return (this->xmin() <= bbox.xmin()) &&
			(this->ymin() <= bbox.ymin()) &&
			(this->xmax() >= bbox.xmax()) &&
			(this->ymax() >= bbox.ymax());
	}
}

bool BoundingBox::contain(float x, float y, bool normalized, bool proper) const {
	if (this->normalized() != normalized)return false;
	if (proper)
	{
		return (this->xmin() < x) &&
			(this->ymin() < y) &&
			(this->xmax() > x) &&
			(this->ymax() > y);
	}
	else
	{
		return (this->xmin() <= x) &&
			(this->ymin() <= y) &&
			(this->xmax() >= x) &&
			(this->ymax() >= y);
	}
}

API_PROTOCOL float CALL_PROTOCOL bboxes_overlap(const BoundingBox& bbox1, const BoundingBox& bbox2, const bool inclass/* = true*/)
{
	return bbox1.overlap(bbox2, inclass);
}