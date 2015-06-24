/**
 * @file
 * Javascript for oa_jira_collector module.
 */
(function ($) {

  Drupal.behaviors.oaJiraCollector = {
    attach: function (context, settings) {
      // Use ajax() instead of getScript() as this allows cache to be enabled.
      // This is preferable for performance reasons. The JIRA Issue Collector
      // script should not change much.
      if (typeof settings.oaJiraCollector != 'undefined') {
        $.ajax({
          url: settings.oaJiraCollector.url,
          type: "get",
          dataType: "script",
          cache: true
        });
      }
    }
  };

  window.ATL_JQ_PAGE_PROPS =  {
    "triggerFunction": function(showCollectorDialog) {
      //Requires that jQuery is available!
      $("#oaJiraCollector:not(.processed)").addClass("processed").click(function(e) {
        e.preventDefault();
        showCollectorDialog();
      });
    }};

})(jQuery);
