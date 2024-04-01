include(FetchContent)

FetchContent_Declare(
  cpr
  GIT_REPOSITORY https://github.com/libcpr/cpr.git
  GIT_TAG        origin/master # You can specify a fixed release tag/version
)

FetchContent_MakeAvailable(cpr)