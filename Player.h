class Player
{
        private:
                int health;
                float x, y,z;
                bool moving;

        public:
            Player(float startX, float startY, float startZ, float playerSize);
            int getHealth(void);
            float getX(void);
            float getY(void);
            float getZ(void);
            void startMoving(int x, int y, int z);
            void stopMoving(void);
            void move(float dx, float dy, float dz);
            void update();
            void draw();
};
