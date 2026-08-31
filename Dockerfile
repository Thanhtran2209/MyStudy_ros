FROM ros:jazzy

# Tạo workspace bên trong container
WORKDIR /ros2_ws

# Copy source code từ host vào image
COPY src ./src

# Cài dependency của package (đọc từ package.xml) rồi build bằng colcon
RUN apt-get update && rosdep update && \
    rosdep install --from-paths src --ignore-src -r -y && \
    rm -rf /var/lib/apt/lists/*

RUN /bin/bash -c "source /opt/ros/jazzy/setup.bash && colcon build"

# Tự động source workspace mỗi khi mở shell mới trong container
RUN echo "source /opt/ros/jazzy/setup.bash" >> /root/.bashrc && \
    echo "source /ros2_ws/install/setup.bash" >> /root/.bashrc

CMD ["bash"]
