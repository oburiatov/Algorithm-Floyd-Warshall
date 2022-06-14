FROM node:14.15-alpine AS build
ENV TARGETPLATFORM=linux/amd64
ARG TARGETPLATFORM=linux/amd64
WORKDIR /app
COPY nodejs/frontend/react-app/. ./
RUN npm install
RUN npm run build

FROM nginx:stable-alpine
COPY --from=build /app/build /usr/share/nginx/html
COPY nodejs/frontend/nginx/nginx.conf /etc/nginx/conf.d/default.conf
# COPY lab1/frontend/nginx/cert/. /etc/nginx/certs/.
EXPOSE 3000
CMD ["nginx", "-g", "daemon off;"]