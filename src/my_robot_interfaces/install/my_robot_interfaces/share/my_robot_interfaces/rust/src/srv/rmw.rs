#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



#[link(name = "my_robot_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__my_robot_interfaces__srv__ResetCounter_Request() -> *const std::ffi::c_void;
}

#[link(name = "my_robot_interfaces__rosidl_generator_c")]
extern "C" {
    fn my_robot_interfaces__srv__ResetCounter_Request__init(msg: *mut ResetCounter_Request) -> bool;
    fn my_robot_interfaces__srv__ResetCounter_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ResetCounter_Request>, size: usize) -> bool;
    fn my_robot_interfaces__srv__ResetCounter_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ResetCounter_Request>);
    fn my_robot_interfaces__srv__ResetCounter_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ResetCounter_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<ResetCounter_Request>) -> bool;
}

// Corresponds to my_robot_interfaces__srv__ResetCounter_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ResetCounter_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub reset_value: i64,

}



impl Default for ResetCounter_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !my_robot_interfaces__srv__ResetCounter_Request__init(&mut msg as *mut _) {
        panic!("Call to my_robot_interfaces__srv__ResetCounter_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ResetCounter_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { my_robot_interfaces__srv__ResetCounter_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { my_robot_interfaces__srv__ResetCounter_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { my_robot_interfaces__srv__ResetCounter_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ResetCounter_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ResetCounter_Request where Self: Sized {
  const TYPE_NAME: &'static str = "my_robot_interfaces/srv/ResetCounter_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__my_robot_interfaces__srv__ResetCounter_Request() }
  }
}


#[link(name = "my_robot_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__my_robot_interfaces__srv__ResetCounter_Response() -> *const std::ffi::c_void;
}

#[link(name = "my_robot_interfaces__rosidl_generator_c")]
extern "C" {
    fn my_robot_interfaces__srv__ResetCounter_Response__init(msg: *mut ResetCounter_Response) -> bool;
    fn my_robot_interfaces__srv__ResetCounter_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ResetCounter_Response>, size: usize) -> bool;
    fn my_robot_interfaces__srv__ResetCounter_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ResetCounter_Response>);
    fn my_robot_interfaces__srv__ResetCounter_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ResetCounter_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<ResetCounter_Response>) -> bool;
}

// Corresponds to my_robot_interfaces__srv__ResetCounter_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ResetCounter_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,

}



impl Default for ResetCounter_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !my_robot_interfaces__srv__ResetCounter_Response__init(&mut msg as *mut _) {
        panic!("Call to my_robot_interfaces__srv__ResetCounter_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ResetCounter_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { my_robot_interfaces__srv__ResetCounter_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { my_robot_interfaces__srv__ResetCounter_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { my_robot_interfaces__srv__ResetCounter_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ResetCounter_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ResetCounter_Response where Self: Sized {
  const TYPE_NAME: &'static str = "my_robot_interfaces/srv/ResetCounter_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__my_robot_interfaces__srv__ResetCounter_Response() }
  }
}






#[link(name = "my_robot_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__my_robot_interfaces__srv__ResetCounter() -> *const std::ffi::c_void;
}

// Corresponds to my_robot_interfaces__srv__ResetCounter
#[allow(missing_docs, non_camel_case_types)]
pub struct ResetCounter;

impl rosidl_runtime_rs::Service for ResetCounter {
    type Request = ResetCounter_Request;
    type Response = ResetCounter_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__my_robot_interfaces__srv__ResetCounter() }
    }
}


