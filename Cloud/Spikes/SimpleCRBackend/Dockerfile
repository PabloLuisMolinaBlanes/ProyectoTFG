FROM node:alpine
WORKDIR /app
COPY package*.json .
COPY tsconfig*.json .
ARG DATABASE_URL="mysql://root:root@db:3306/CloudDatabase"
ARG DATABASE_USER="root"
ARG DATABASE_PASSWORD="root"
ARG DATABASE_NAME="CloudDatabase"
ARG DATABASE_HOST="localhost"
ARG DATABASE_PORT=3306
RUN npm install
COPY . .
RUN touch .env
RUN printenv > .env
RUN npx prisma generate
RUN mkdir build
RUN mkdir build/src
RUN cp -R src/generated build/src/generated
CMD ["npm", "run", "dev"]