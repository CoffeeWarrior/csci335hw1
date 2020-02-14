// --> YOUR NAME here
// Few comments describing the class Points2

#ifndef CSCI335_HOMEWORK1_POINTS2_H_
#define CSCI335_HOMEWORK1_POINTS2_H_

#include <array>
#include <cstddef>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
namespace teaching_project {
// Place comments that provide a brief explanation of the class,
// and its sample usage.
template<typename Object>
class Points2 {
 public:
  // Default "big five" -- you have to alter them for your assignment.
  // That means that you will remove the "= default" statement.
  //  and you will provide an implementation.


  // Zero-parameter constructor. 
  // Set size to 0.
  Points2(){
    size_ = 0;
    sequence_ = nullptr;
  };



  // Copy-constructor.
  Points2(const Points2 &rhs) : size_(rhs.size_){
    sequence_ = new std::array<Object, 2>[size_];
    for(size_t i = 0; i< size_; i++){
      sequence_[i][0] = rhs.sequence_[i][0]; // copy rvalue not lval
      sequence_[i][1] = rhs.sequence_[i][1];
    }
  };




  // Copy-assignment. If you have already written
  // the copy-constructor and the move-constructor
  // you can just use:
  // {
  // Points2 copy = rhs; 
  // std::swap(*this, copy);
  // return *this;
  // }
  Points2& operator=(const Points2 &rhs){
    Points2 copy = rhs;
    std::swap(*this, copy);
    return *this;
  };



  // Move-constructor. 
  Points2(Points2 &&rhs){ 
    size_ = rhs.size_;
    sequence_ = rhs.sequence_;
  };




  // Move-assignment.
  // Just use std::swap() for all variables.
  Points2& operator=(Points2 &&rhs){ //followed comment left by prof
    std::swap(sequence_, rhs.sequence_);
    std::swap(size_, rhs.size_);
    return *this;
  };

  ~Points2(){
    delete[] sequence_; 
  };

  // End of big-five.



  // One parameter constructor.
  Points2(const std::array<Object, 2>& item) { //sets sequence
    sequence_ = new std::array<Object, 2>;
    size_= 1;
    sequence_[0][0] = item[0];
    sequence_[0][1] = item[1];
  }




  // Read a chain from standard input.
  void ReadPoints2() {
    // Part of code included (without error checking).
    std::string input_line;
    std::getline(std::cin, input_line); 
    std::stringstream input_stream(input_line);
    if (input_line.empty()) return;
    // Read size of sequence (an integer).
    
    int size_of_sequence;
    input_stream >> size_of_sequence;
    // Allocate space for sequence.
    // Add code here.


    delete[] sequence_;
    sequence_ = new std::array<Object, 2>[size_of_sequence]; //update sequence

    Object token;
    for (int i = 0 ;input_stream >> token; ++i) { 
      // Read coordinates.
      // Fill sequence_ here.
      int entry = i%2; //will give whether its the x or y coordinate of point, as there are 2x as many entries as points
      int pointIndex = i/2; //integer division, drops fractional part, will always round down 
      sequence_[pointIndex][entry] = token; 
    }
    
    size_ = size_of_sequence;
  }

  size_t size() const { // I know yall want me to comment everything but fr look at this
    return size_;
  }


  // @location: an index to a location in the sequence.
  // @returns the point at @location.
  // const version.
  // abort() if out-of-range.
  const std::array<Object, 2>& operator[](size_t location) const { 
    if(location >= size_){ //aborts if accessing out of range 
      std::abort();
    }
    return sequence_[location];
  }



 //  @c1: A sequence.
 //  @c2: A second sequence.
 //  @return their sum. If the sequences are not of the same size, append the
 //    result with the remaining part of the larger sequence.
// Suppose A = (1, 2) (3, 4) (5, 6) and B = (7, 8) (9, 10). Then A + B = (8, 10) (12, 14) (5, 6).
    void updateSequence(std::array<Object, 2>*new_sequence, size_t size){  //this function will update a sequence of a given points2 object
      delete[] sequence_;                                                  //so that I can do the + operator without blowing my brains out
      sequence_= new_sequence;
      size_ = size;
    }

		friend Points2 operator+(const Points2& c1, const Points2& c2) { //this will add 2 objects as specified by ralph vente on blackboard
      Points2 larger, smaller; //this will find the smaller and larger sized points2 object so the code after the else statement doesnt need to be repeated
      if(c1.size_ >= c2.size_){
        larger =  c1;
        smaller = c2;
      }else{
        larger = c2;
        smaller = c1;
      }
      std::array<Object, 2> *new_sequence;
      new_sequence = new std::array<Object, 2>[larger.size_];
      
      for(size_t i = 0; i < smaller.size_; i++){
        new_sequence[i][0] = larger[i][0] + smaller[i][0];
        new_sequence[i][1] = larger[i][1] + smaller[i][1];
      }
      for(size_t i = smaller.size_; i< larger.size_; i++){
        new_sequence[i][0] = larger[i][0];
        new_sequence[i][1] = larger[i][1];
      }
      Points2 result;
      result.updateSequence(new_sequence, larger.size_); //uses helper function above
    return result;
		}


		// Overloading the << operator.
		friend std::ostream& operator<<(std::ostream& out, const Points2& some_points2) {
			if (some_points2.size_ == 0) { //print parenthesis if empty
				out << "()";
			} else {
        for (std::size_t i = 0; i < some_points2.size_; ++i) { //output points in parenthesized w/ commas
				  out << "(" << some_points2.sequence_[i][0] << ", " << some_points2.sequence_[i][1] << ") ";
			  }
      }
			out << '\n';
			return out;
		}
/**************************************************************************************/
 private:
  // Sequence of points. 
  std::array<Object, 2> *sequence_;
  // Size of sequence.
  size_t size_;

};

}  // namespace teaching_project
#endif // CSCI_335_HOMEWORK1_POINTS2_H_
