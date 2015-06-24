<script type="text/javascript" src="<?php print $collector; ?>"></script>
<script type="text/javascript">window.ATL_JQ_PAGE_PROPS =  {
    "triggerFunction": function(showCollectorDialog) {
      //Requires that jQuery is available!
      jQuery("#myCustomTrigger").click(function(e) {
        e.preventDefault();
        showCollectorDialog();
      });
    }};</script>

<button id="myCustomTrigger" class="aui-button aui-button-primary" type="submit" name="confirm" value="Save" tabindex="101" data-tooltip="<?php print $caption; ?>">
  <span class="trigger-text"><?php print $caption; ?></span>
</button>
