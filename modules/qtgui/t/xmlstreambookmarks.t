#!/usr/bin/perl

package XmlStreamBookmarksTest;

use strict;
use warnings;
use QtCore;
use QtGui4;
use QtTest4;
use MainWindow;
use QtCore::isa qw(Qt::Object);
use QtCore::slots
    private => 1,
    initTestCase => [],
    verifyItemCount => [],
    identicalWrite => [],
    modifiedWrite => [],
    cleanupTestCase => [];
use Test::More;

my $xbelfile = <<EOF;
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE xbel>
<xbel version="1.0">
    <folder folded="yes">
        <title>Literate Programming</title>
        <bookmark href="http://www.vivtek.com/litprog.html">
            <title>Synopsis of Literate Programming</title>
        </bookmark>
        <bookmark href="http://vasc.ri.cmu.edu/old_help/Programming/Literate/literate.html">
            <title>Literate Programming: Propaganda and Tools</title>
        </bookmark>
        <bookmark href="http://www.isy.liu.se/%7Eturbell/litprog/">
            <title>Literate Programming by Henrik Turbell</title>
        </bookmark>
        <bookmark href="http://www.desy.de/user/projects/LitProg.html">
            <title>Literate Programming Library</title>
        </bookmark>
        <bookmark href="http://www.loria.fr/services/tex/english/litte.html">
            <title>Literate Programming Basics</title>
        </bookmark>
        <bookmark href="http://ei.cs.vt.edu/%7Ecs5014/courseNotes/4.LiterateProgramming/literate_prog.html">
            <title>Literate Programming Overview</title>
        </bookmark>
        <bookmark href="http://www.perl.com/pub/a/tchrist/litprog.html">
            <title>POD is not Literate Programming</title>
        </bookmark>
        <bookmark href="http://www.cornellcollege.edu/%7Eltabak/publications/articles/swsafety.html">
            <title>Computers That We Can Count On</title>
        </bookmark>
        <bookmark href="http://www.cs.auc.dk/%7Enormark/litpro/issues-and-problems.html">
            <title>Literate Programming - Issues and Problems</title>
        </bookmark>
        <bookmark href="http://c2.com/cgi/wiki?LiterateProgramming">
            <title>Literate Programming - Wiki Pages</title>
        </bookmark>
        <bookmark href="http://developers.slashdot.org/developers/02/05/19/2216233.shtml">
            <title>What is well-commented code?</title>
        </bookmark>
        <bookmark href="http://liinwww.ira.uka.de/bibliography/SE/litprog.html">
            <title>Bibliography on literate programming - A searchable bibliography</title>
        </bookmark>
        <bookmark href="http://www2.umassd.edu/SWPI/ProcessBibliography/bib-codereading.html">
            <title>Program comprehension and code reading bibliography</title>
        </bookmark>
        <bookmark href="http://www.cs.auc.dk/%7Enormark/elucidative-programming/">
            <title>Elucidative Programming</title>
        </bookmark>
        <bookmark href="http://www.msu.edu/%7Epfaffben/avl/index.html">
            <title>AVL Trees (TexiWeb)</title>
        </bookmark>
        <bookmark href="http://literate-programming.wikiverse.org/">
            <title>Literate Programming on Wikiverse</title>
        </bookmark>
        <bookmark href="http://www.pbrt.org/">
            <title>Physically Based Rendering: From Theory to Implementation</title>
        </bookmark>
    </folder>
    <folder folded="no">
        <title>Useful C++ Links</title>
        <folder folded="no">
            <title>STL</title>
            <bookmark href="http://www.sgi.com/tech/stl/table_of_contents.html">
                <title>STL Reference Documentation</title>
            </bookmark>
            <bookmark href="http://www.yrl.co.uk/~phil/stl/stl.htmlx">
                <title>STL Tutorial</title>
            </bookmark>
            <bookmark href="http://www.cppreference.com/cpp_stl.html">
                <title>STL Reference</title>
            </bookmark>
        </folder>
        <folder folded="no">
            <title>Qt</title>
            <bookmark href="http://qt.nokia.com/doc/2.3/">
                <title>Qt 2.3 Reference</title>
            </bookmark>
            <bookmark href="http://qt.nokia.com/doc/3.3/">
                <title>Qt 3.3 Reference</title>
            </bookmark>
            <bookmark href="http://qt.nokia.com/doc/4.0/">
                <title>Qt 4.0 Reference</title>
            </bookmark>
            <bookmark href="http://qt.nokia.com/">
                <title>Qt Home Page</title>
            </bookmark>
        </folder>
        <folder folded="yes">
            <title>IOStreams</title>
            <bookmark href="http://www.cplusplus.com/ref/iostream/index.html">
                <title>IO Stream Library</title>
            </bookmark>
            <bookmark href="http://courses.cs.vt.edu/~cs2604/fall01/binio.html">
                <title>Binary I/O</title>
            </bookmark>
            <bookmark href="http://www.parashift.com/c++-faq-lite/input-output.html">
                <title>I/O Stream FAQ</title>
            </bookmark>
        </folder>
        <folder folded="yes">
            <title>gdb</title>
            <bookmark href="http://www.cs.princeton.edu/~benjasik/gdb/gdbtut.html">
                <title>GDB Tutorial</title>
            </bookmark>
            <bookmark href="http://www.gnu.org/manual/gdb-4.17/html_mono/gdb.html">
                <title>Debugging with GDB</title>
            </bookmark>
            <bookmark href="http://www.cs.washington.edu/orgs/acm/tutorials/dev-in-unix/gdb-refcard.pdf">
                <title>GDB Quick Reference Page (PDF) (Handy)</title>
            </bookmark>
        </folder>
        <folder folded="yes">
            <title>Classes and Constructors</title>
            <bookmark href="http://www.parashift.com/c++-faq-lite/ctors.html">
                <title>Constructor FAQ</title>
            </bookmark>
            <bookmark href="http://www.juicystudio.com/tutorial/cpp/index.html">
                <title>Organizing Classes</title>
            </bookmark>
        </folder>
    </folder>
    <folder folded="yes">
        <title>Software Documentation or System Documentation</title>
        <bookmark href="http://www.martinfowler.com/distributedComputing/thud.html">
            <title>The Almighty Thud</title>
        </bookmark>
        <bookmark href="http://msdn.microsoft.com/library/techart/cfr.htm">
            <title>Microsoft Coding Techniques and Programming Practices</title>
        </bookmark>
        <bookmark href="http://www.bearcave.com/software/prog_docs.html">
            <title>Software and Documentation</title>
        </bookmark>
        <bookmark href="http://c2.com/cgi/wiki?TheSourceCodeIsTheDesign">
            <title>The Source Code is the Design</title>
        </bookmark>
        <bookmark href="http://www.bleading-edge.com/Publications/C++Journal/Cpjour2.htm">
            <title>What is Software Design?</title>
        </bookmark>
        <bookmark href="http://www.mindprod.com/unmain.html">
            <title>How To Write Unmaintainable Code</title>
        </bookmark>
        <bookmark href="http://www.idinews.com/selfDoc.html">
            <title>Self Documenting Program Code Remains a Distant Goal</title>
        </bookmark>
        <bookmark href="http://www.sdmagazine.com/documents/s=730/sdm0106m/0106m.htm">
            <title>Place Tab A in Slot B</title>
        </bookmark>
        <bookmark href="http://www.holub.com/class/uml/uml.html">
            <title>UML Reference Card</title>
        </bookmark>
    </folder>
    <folder folded="yes">
        <title>TeX Resources</title>
        <bookmark href="http://www.tug.org/">
            <title>The TeX User's Group</title>
        </bookmark>
        <bookmark href="http://www.miktex.org/">
            <title>MikTeX website</title>
        </bookmark>
        <bookmark href="http://cm.bell-labs.com/who/hobby/MetaPost.html">
            <title>MetaPost website</title>
        </bookmark>
        <bookmark href="http://pauillac.inria.fr/%7Emaranget/hevea/">
            <title>HEVEA is a quite complete and fast LATEX to HTML translator</title>
        </bookmark>
    </folder>
    <folder folded="no">
        <title>Portable Document Format (PDF)</title>
        <bookmark href="http://www.adobe.com/">
            <title>Adobe - The postscript and PDF standards</title>
        </bookmark>
        <bookmark href="http://partners.adobe.com/asn/developer/technotes/acrobatpdf.html">
            <title>Reference Manual Portable Document Format</title>
        </bookmark>
        <bookmark href="http://partners.adobe.com/asn/developer/acrosdk/main.html">
            <title>Adobe Acrobat Software Development Kit</title>
        </bookmark>
    </folder>
    <folder folded="yes">
        <title>Literature Sites</title>
        <bookmark href="http://www.cc.columbia.edu/cu/libraries/subjects/speccol.html">
            <title>Guide to Special Collections (Columbia University)</title>
        </bookmark>
        <bookmark href="http://www.ipl.org/ref/litcrit/">
            <title>Literary Criticism on the Web from the Internet Public Library</title>
        </bookmark>
        <bookmark href="http://www.victorianweb.org/">
            <title>Victorian Web.</title>
        </bookmark>
        <bookmark href="http://vos.ucsb.edu/">
            <title>Voice of the Shuttle.</title>
        </bookmark>
        <bookmark href="http://www.modjourn.brown.edu/">
            <title>Modernist Journals Project</title>
        </bookmark>
        <bookmark href="http://www.poetspath.com">
            <title>Museum of American Poetics</title>
        </bookmark>
        <bookmark href="http://www.english.uiuc.edu/maps/">
            <title>Modern American Poetry</title>
        </bookmark>
        <bookmark href="http://www.findarticles.com/">
            <title>FindArticles.com</title>
        </bookmark>
        <bookmark href="http://www.literaryhistory.com">
            <title>Literary History</title>
        </bookmark>
        <bookmark href="http://www.litencyc.com/LitEncycFrame.htm">
            <title>Literary Encyclopedia</title>
        </bookmark>
        <separator/>
        <bookmark href="http://texts.cdlib.org/ucpress/">
            <title>The University of California Press</title>
        </bookmark>
        <bookmark href="http://www.letrs.indiana.edu/web/w/wright2/">
            <title>Wright American Fiction, 1851-1875</title>
        </bookmark>
        <bookmark href="http://docsouth.unc.edu/">
            <title>Documenting the American South: Beginnings to 1920</title>
        </bookmark>
        <bookmark href="http://etext.lib.virginia.edu/eng-on.html">
            <title>Electronic Text Center at the University of Virginia</title>
        </bookmark>
        <bookmark href="http://digital.nypl.org/schomburg/writers_aa19/">
            <title>The Schomburg Center for Research in Black Culture</title>
        </bookmark>
        <bookmark href="http://www.infomotions.com/alex2/">
            <title>Alex Catalogue of Electronic Texts.</title>
        </bookmark>
    </folder>
</xbel>
EOF

sub NEW {
    my ($class, $parent) = @_;
    $class->SUPER::NEW();
}

sub initTestCase {
    my $testFile = 'test.xbel';
    open my $xbelfh, '>', $testFile;
    print $xbelfh $xbelfile;
    close $xbelfh;

    my $mainWin = MainWindow();
    $mainWin->show();
    $mainWin->open($testFile);
    this->{mainWin} = $mainWin;
}

sub countItems {
    my ($item) = @_;
    my $itemCount = $item->childCount();
    foreach my $itemNum (0..$itemCount-1) {
        $itemCount += countItems($item->child($itemNum));
    }
    return $itemCount;
}

sub verifyItemCount {
    my $mainWin = this->{mainWin};
    my $treeWidget = $mainWin->{treeWidget};
    is( $treeWidget->topLevelItemCount(), 6, 'topLevelItemCount' );

    my $itemCount += $treeWidget->topLevelItemCount();
    foreach my $itemNum (0..$treeWidget->topLevelItemCount()-1) {
        $itemCount += countItems($treeWidget->topLevelItem($itemNum));
    }
    is( $itemCount, 76, 'totalItemCount' );
}

sub identicalWrite {
    this->{mainWin}->saveAs('test2.xbel');
    my $diff = `diff test.xbel test2.xbel`;
    is( $diff, '', 'identicalWrite' );
    unlink 'test2.xbel';
}

sub modifiedWrite {
    my $mainWin = this->{mainWin};
    my $treeWidget = $mainWin->{treeWidget};
    my $item = $treeWidget->topLevelItem(1)->child(0)->child(0);

    foreach my $col (0..1) {
        my $itemRect = $treeWidget->visualRect($treeWidget->indexFromItem($item, $col));
        Qt::Test::mouseClick( $treeWidget->viewport(), Qt::LeftButton(), Qt::NoModifier(), $itemRect->center() );
        Qt::Test::mouseDClick( $treeWidget->viewport(), Qt::LeftButton(), Qt::NoModifier(), $itemRect->center() );
        my $text;
        if ( $col == 0 ) {
            $text = 'PerlQt Rocks!';
        }
        else {
            $text = 'http://www.kde.org';
        }
        my $delegate = ($treeWidget->findChildren( 'Qt::LineEdit' ))[0]->[0];
        Qt::Test::keyClicks( $delegate, $text );
        Qt::Test::qWait(100);
        Qt::Test::keyClick( $delegate, Qt::Key_Enter() );
        Qt::Test::qWait(100);
    }

    my $expectedDiff = <<EOF;
62,63c62,63
<             <bookmark href="http://www.sgi.com/tech/stl/table_of_contents.html">
<                 <title>STL Reference Documentation</title>
---
>             <bookmark href="http://www.kde.org">
>                 <title>PerlQt Rocks!</title>
EOF

    this->{mainWin}->saveAs('test2.xbel');
    my $diff = `diff test.xbel test2.xbel`;
    is( $diff, $expectedDiff, 'modifiedWrite' );
    unlink 'test2.xbel';
}

sub cleanupTestCase {
    unlink 'test.xbel';
}

package main;

use strict;
use warnings;

use QtCore;
use QtGui4;
use QtTest4;
use XmlStreamBookmarksTest;
use Test::More tests=>4;

# [0]
sub main
{
    my $app = Qt::Application(\@ARGV);
    my $test = XmlStreamBookmarksTest();
    unshift @ARGV, $0;
    return Qt::Test::qExec($test, scalar @ARGV, \@ARGV);
}
# [0]

exit main();
