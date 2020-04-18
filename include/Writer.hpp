#ifndef MD_AUDIO_WRITER_HPP
#define MD_AUDIO_WRITER_HPP

#include "Buffer.hpp"

namespace md_audio {

    template <typename Allocator>
    class Writer {
    public:
        explicit Writer(Allocator&, std::uint32_t);

        virtual void initialise();

        virtual void write(MdFloat) noexcept final;

        virtual void increment(void) noexcept final;

        virtual ~Writer() = 0;

    protected:
        std::uint32_t m_write_index = 0;
        std::uint32_t m_upper_bound_1;
        Buffer<Allocator> m_buffer;
    };

    template <typename Allocator>
    Writer<Allocator>::Writer(Allocator& allocator, std::uint32_t upper_bound) :
        m_buffer(allocator, upper_bound),
        m_upper_bound_1(upper_bound - 1)
    {}

    template <typename Allocator>
    void Writer<Allocator>::initialise() {
        m_buffer.initialise();
    }

    template <typename Allocator>
    void Writer<Allocator>::write(MdFloat in) noexcept {
        m_buffer[m_write_index] = in;
    }

    template <typename Allocator>
    void Writer<Allocator>::increment() noexcept {
        m_write_index = utility::wrap(m_write_index + 1, 0, m_upper_bound_1);
    }

    template <typename Allocator>
    Writer<Allocator>::~Writer() {}

}

#endif /* MD_AUDIO_WRITER_HPP */
