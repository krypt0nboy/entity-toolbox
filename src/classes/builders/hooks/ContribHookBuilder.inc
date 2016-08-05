<?php

/**
 * Class ContribHookBuilder
 *
 * Used to build data when toolbox_info is required.
 */
class ContribHookBuilder extends HookBuilder {
  /**
   * @var array $toolboxInfo
   *   The entity type toolbox info.
   */
  protected $toolboxInfo = array();

  /** {{@inheritdoc}} */
  public function __construct($hook, $entityType, array $rawData = array()) {
	parent::__construct($hook, $entityType, $rawData);
	$this->toolboxInfo = entity_toolbox_get_info($entityType);
  }
}