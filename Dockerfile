# Build image
FROM alpine as build-env
RUN apk add --no-cache build-base make
COPY /project0 /app
WORKDIR /app
# Compile the binaries
RUN make

# Run image
# FROM alpine
# COPY --from=build-env /app /app
# WORKDIR /app
# # CMD ["/app/hello"] 