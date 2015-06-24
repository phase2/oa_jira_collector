<?php

/**
 * @file
 * Defines the JIRA Issue Collector widget.
 */

$plugin = array(
  'title' => t('JIRA Issue Collector'),
  'description' => t('Display a button for adding an issue via the JIRA Issue Collector.'),
  'single' => TRUE,
  'category' => t('JIRA'),
  'edit form' => 'oa_jira_collector_edit_form',
  'render callback' => 'oa_jira_collector_render',
  'defaults' => array(
    'token_title' => '',
    'token_body' => '',
  ),
);


/**
 * Render callback for the widget.
 */
function oa_jira_collector_render($subtype, $conf, $args, $context = NULL) {

  $block = new stdClass();
  $block->title = '';

  $collector = $conf['collector'];

  $output = '<script type="text/javascript"
    src="' . $collector . '"></script>
    <script type="text/javascript">window.ATL_JQ_PAGE_PROPS =  {
	    "triggerFunction": function(showCollectorDialog) {
		    //Requires that jQuery is available!
		    jQuery("#myCustomTrigger").click(function(e) {
			    e.preventDefault();
			    showCollectorDialog();
		});
	}};</script>

  <button id="myCustomTrigger" class="aui-button aui-button-primary" type="submit" name="confirm" value="Save" tabindex="101" data-tooltip="Submit a bug report">
    <span class="trigger-text">Submit Feedback</span>
  </button>';
  $vars['collector'] = $collector;
  $vars['caption'] = !empty($conf['caption']) ? $conf['caption'] : t('Submit an issue');
  $block->content = theme('oa_jira_collector', $vars);

  return $block;
}

/**
 * Edit form for the panel.
 */
function oa_jira_collector_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];
  $form['override_title']['#access'] = FALSE;
  $form['override_title_text']['#access'] = FALSE;
  $form['token_title'] = array(
    '#title' => t('Displayed Title'),
    '#description' => t('Enter the title to be displayed, including any token references.'),
    '#type' => 'textfield',
    '#default_value' => $conf['token_title'],
  );
  $form['token_body'] = array(
    '#title' => t('Displayed Text'),
    '#description' => t('Enter the full text to be displayed, including any token references.'),
    '#type' => 'text_format',
    '#format' => isset($conf['token_body']['format']) ? $conf['token_body']['format'] : 'panopoly_wysiwyg_text',
    '#default_value' => isset($conf['token_body']['value']) ? $conf['token_body']['value'] : '',
  );
  $form['tokens'] = array(
    '#theme' => 'token_tree',
    '#token_types' => array('node'),
    '#recursion_limit' => 2,
  );

  return $form;
}

/**
 * Submit handler for edit form. Save the custom form fields we added.
 */
function oa_jira_collector_edit_form_submit($form, &$form_state) {
  foreach (array_keys($form_state['plugin']['defaults']) as $key) {
    if (isset($form_state['values'][$key])) {
      $form_state['conf'][$key] = $form_state['values'][$key];
    }
  }
}

