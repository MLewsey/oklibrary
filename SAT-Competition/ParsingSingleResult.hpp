// Oliver Kullmann, 13.5.2005 (Swansea)

#ifndef PARSINGSINGLERESULT_jzRtL77Yq1

#define PARSINGSINGLERESULT_jzRtL77Yq1

#include <string>

#include <boost/spirit/core.hpp>

#include "ParserBase.hpp"

#include "SingleResult.hpp"

namespace OKlib {

  namespace SATCompetition {

    using ::OKlib::Parser::ParseIterator;
    
    using ::OKlib::Parser::Rule;
    
    using ::OKlib::Parser::ParserBase;
    
    template <class ResultElement>
    class ParserResultElement;

    // ---------------------------------------------------------------------------------------------------------

    template <>
    class ParserResultElement<SuperSeries> : public ParserBase {
      SuperSeries& s;
      struct action {
        SuperSeries& s;
        action(SuperSeries& s) : s(s) {}
        void operator() (const ParseIterator begin, const ParseIterator end) const {
          s = SuperSeries(std::string(begin, end));
        }
      };
    public :
      ParserResultElement(SuperSeries& s) : s(s) {
        parser_ = (+(boost::spirit::alnum_p | boost::spirit::ch_p('-')))[action(s)];
      }
    };
   template <>
    class ParserResultElement<RandomKSat> : public ParserBase {
      RandomKSat& s;
      NaturalNumber k;
      struct action1 {
        NaturalNumber& k;
        action1(NaturalNumber& k) : k(k) {}
        void operator() (NaturalNumber k_) const {
          k = k_;
        }
      };
      struct action2 {
        NaturalNumber& k;
        RandomKSat& s;
        action2(NaturalNumber& k, RandomKSat& s) : k(k), s(s) {}
        void operator() (const ParseIterator begin, const ParseIterator end) const {
          s = RandomKSat(std::string(begin, end), k);
        }
      };
    public :
      ParserResultElement(RandomKSat& s) : s(s) {
        parser_ = ((boost::spirit::uint_parser<NaturalNumber, 10, 1, 2>())[action1(k)] >> boost::spirit::str_p("SAT"))[action2(k,s)];
      }
    };

    // ---------------------------------------------------------------------------------------------------------

    template <>
    class ParserResultElement<Series> : public ParserBase {
      Series& s;
      struct action {
        Series& s;
        action(Series& s) : s(s) {}
        void operator() (const ParseIterator begin, const ParseIterator end) const {
          s = Series(std::string(begin, end));
        }
      };
      Rule filename;
    public :
      ParserResultElement(Series& s) : s(s) {
        filename = +(boost::spirit::alnum_p | boost::spirit::ch_p('-') | boost::spirit::ch_p('.'));
        parser_ = (+(filename >> boost::spirit::ch_p('/')) >> filename)[action(s)];
      }
    };

    template <>
    class ParserResultElement<RandomKSat_n> : public ParserBase {
      RandomKSat_n& s;
      NaturalNumber n;
      struct action1 {
        NaturalNumber& n;
        action1(NaturalNumber& n) : n(n) {}
        void operator() (const NaturalNumber n_) const {
          n = n_;
        }
      };
      struct action2 {
        NaturalNumber& n;
        RandomKSat_n& s;
        action2(NaturalNumber& n, RandomKSat_n& s) : n(n), s(s) {}
        void operator() (const ParseIterator begin, const ParseIterator end) const {
          s = RandomKSat_n(std::string(begin, end), n);
        }
      };
      Rule filename;
      Rule basename;
    public :
      ParserResultElement(RandomKSat_n& s) : s(s) {
        filename = +(boost::spirit::alnum_p | boost::spirit::ch_p('-'));
        basename = +(
                     boost::spirit::alnum_p  |
                     boost::spirit::ch_p('.') |
                     (boost::spirit::ch_p('-') >> ((boost::spirit::alnum_p - boost::spirit::ch_p('v')) | boost::spirit::ch_p('.') | boost::spirit::ch_p('-'))) |
                     (boost::spirit::str_p("-v") >> (boost::spirit::alpha_p | boost::spirit::ch_p('.') | boost::spirit::ch_p('-')) |
                     (boost::spirit::str_p("-v") >> boost::spirit::uint_p >>
                      (boost::spirit::alpha_p | boost::spirit::ch_p('.') | boost::spirit::ch_p('-'))))
                     )
          >> boost::spirit::str_p("-v") >> boost::spirit::uint_p[action1(n)];
        parser_ = (+(filename >> boost::spirit::ch_p('/')) >> basename)[action2(n,s)];
        //parser_ = *boost::spirit::ch_p('a') >> boost::spirit::str_p("ab"); //CAUTION: does not accept "ab"
      }
    };

    // ---------------------------------------------------------------------------------------------------------

    template <>
    class ParserResultElement<Benchmark> : public ParserBase {
      Benchmark& s;
      struct action {
        Benchmark& s;
        action(Benchmark& s) : s(s) {}
        void operator() (const ParseIterator begin, const ParseIterator end) const {
          s = Benchmark(std::string(begin, end));
        }
      };
    public :
      ParserResultElement(Benchmark& s) : s(s) {
        parser_ = (boost::spirit::str_p("bench") >> boost::spirit::uint_p)[action(s)];
      }
    };

    // ---------------------------------------------------------------------------------------------------------

    template <>
    class ParserResultElement<Solver> : public ParserBase {
      Solver& s;
      struct action {
        Solver& s;
        action(Solver& s) : s(s) {}
        void operator() (const ParseIterator begin, const ParseIterator end) const {
          s = Solver(std::string(begin, end));
        }
      };
    public :
      ParserResultElement(Solver& s) : s(s) {
        parser_ = (boost::spirit::str_p("solver") >> boost::spirit::uint_p)[action(s)];
      }
    };

    // ---------------------------------------------------------------------------------------------------------

    template <>
    class ParserResultElement<SATStatus> : public ParserBase {
      SATStatus& s;
      struct action {
        SATStatus& s;
        action(SATStatus& s) : s(s) {}
        void operator() (const ParseIterator begin, const ParseIterator end) const {
          const std::string status(begin, end);
          if (status == "0")
            s = SATStatus(unknown);
          else if (status == "10")
            s = SATStatus(sat);
          else
            s = SATStatus(unsat);
        }
      };
    public :
      ParserResultElement(SATStatus& s) : s(s) {
        parser_ = (boost::spirit::str_p("0") | boost::spirit::str_p("10") | boost::spirit::str_p("20"))[action(s)];
      }
    };

    // ---------------------------------------------------------------------------------------------------------

    template <>
    class ParserResultElement<AverageTime> : public ParserBase {
      AverageTime& s;
      struct action {
        AverageTime& s;
        action(AverageTime& s) : s(s) {}
        void operator() (const FloatingPoint x) const {
          s = AverageTime(x);
        }
      };
    public :
      ParserResultElement(AverageTime& s) : s(s) {
        parser_ = boost::spirit::real_parser<FloatingPoint, boost::spirit::ureal_parser_policies<FloatingPoint> >()[action(s)];
      }
    };

    // ---------------------------------------------------------------------------------------------------------
    
    template <>
    class ParserResultElement<TimeOut> : public ParserBase {
      TimeOut& s;
      struct action {
        TimeOut& s;
        action(TimeOut& s) : s(s) {}
        void operator() (const NaturalNumber x) const {
          s = TimeOut(x);
        }
      };
    public :
      ParserResultElement(TimeOut& s) : s(s) {
        parser_ = boost::spirit::uint_p[action(s)];
      }
    };

    // ---------------------------------------------------------------------------------------------------------
    // ---------------------------------------------------------------------------------------------------------

    template <class Result>
    class ParserResult;

    template <>
    class ParserResult<Result> : public ParserBase {
      Result& r;
      ParserResultElement<SuperSeries> p_sup_ser;
      ParserResultElement<Series> p_ser;
      ParserResultElement<Benchmark> p_bench;
      ParserResultElement<Solver> p_solv;
      ParserResultElement<SATStatus> p_sat_stat;
      ParserResultElement<AverageTime> p_avg;
      ParserResultElement<TimeOut> p_tmo;
    public :
      typedef Result result_type;
      ParserResult(Result& r) : r(r), p_sup_ser(*r.sup_ser), p_ser(*r.ser), p_bench(*r.bench), p_solv(*r.solv), p_sat_stat(*r.sat_stat), p_avg(*r.avg), p_tmo(*r.tmo) {
        parser_ = p_sup_ser.parser() >> boost::spirit::ch_p(' ') >> p_ser.parser() >> boost::spirit::ch_p(' ') >> p_bench.parser() >> boost::spirit::ch_p(' ') >> p_solv.parser() >> boost::spirit::ch_p(' ') >> p_sat_stat.parser() >> boost::spirit::ch_p(' ') >> p_avg.parser() >> boost::spirit::ch_p(' ') >> p_tmo.parser();
      }
    };

    template <>
    class ParserResult<ResultRandomSat> : public ParserBase {
      ResultRandomSat& r;
      ParserResultElement<RandomKSat> p_sup_ser;
      ParserResultElement<RandomKSat_n> p_ser;
      ParserResultElement<Benchmark> p_bench;
      ParserResultElement<Solver> p_solv;
      ParserResultElement<SATStatus> p_sat_stat;
      ParserResultElement<AverageTime> p_avg;
      ParserResultElement<TimeOut> p_tmo;
    public :
      typedef ResultRandomSat result_type;
      ParserResult(ResultRandomSat& r) : r(r), p_sup_ser(*r.sup_ser), p_ser(*r.ser), p_bench(*r.bench), p_solv(*r.solv), p_sat_stat(*r.sat_stat), p_avg(*r.avg), p_tmo(*r.tmo) {
        parser_ = p_sup_ser.parser() >> boost::spirit::ch_p(' ') >> p_ser.parser() >> boost::spirit::ch_p(' ') >> p_bench.parser() >> boost::spirit::ch_p(' ') >> p_solv.parser() >> boost::spirit::ch_p(' ') >> p_sat_stat.parser() >> boost::spirit::ch_p(' ') >> p_avg.parser() >> boost::spirit::ch_p(' ') >> p_tmo.parser();
      }
    };

    // ---------------------------------------------------------------------------------------------------------
    // ---------------------------------------------------------------------------------------------------------

    template <class ParserResult, class OutputIterator>
    class ParserResultSequence : public ParserBase {
      OutputIterator& begin;
      typedef typename ParserResult::result_type Result;
      Result r;
      ParserResult p;
      struct action {
        OutputIterator& begin;
        Result& r;
        action(OutputIterator& begin, Result& r) : begin(begin), r(r) {}
        void operator() (ParseIterator, ParseIterator) const {
          *begin++ = r;
        }
      };
    public :
      ParserResultSequence(OutputIterator& begin) : begin(begin), p(r) {
        parser_ = +((p.parser() >> boost::spirit::eol_p)[action(begin, r)]);
      }
    };

    template <class ParserResult, class OutputIterator>
    // ToDo: Conceptualisation
    // ParserResult is a parser for results
    // OutputIterator::value_type is Result
    struct Copy_results {
      boost::spirit::parse_info<> operator() (const ParseIterator begin_in, const ParseIterator end_in, OutputIterator begin_out) {
        ParserResultSequence<ParserResult, OutputIterator> p(begin_out);
        return boost::spirit::parse(begin_in, end_in, p.parser());
      }
      template <typename PIterator>
      boost::spirit::parse_info<> operator() (const PIterator begin_in, OutputIterator begin_out) {
        ParserResultSequence<ParserResult, OutputIterator> p(begin_out);
        return boost::spirit::parse(begin_in, p.parser());
      }
    };
    template <class ParserResult, class OutputIterator>
    boost::spirit::parse_info<> copy_results(const ParseIterator begin_in, const ParseIterator end_in, const OutputIterator begin_out) {
      return Copy_results<ParserResult, OutputIterator>()(begin_in, end_in, begin_out);
    }
    template <class ParserResult, typename PIterator, class OutputIterator>
    boost::spirit::parse_info<> copy_results(const PIterator begin_in, const OutputIterator begin_out) {
      return Copy_results<ParserResult, OutputIterator>()(begin_in, begin_out);
    }


  }

}

#endif
