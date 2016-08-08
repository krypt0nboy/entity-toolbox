<?php

/**
 * Class ContribArrayBuilder
 */
class ContribArrayBuilder extends ArrayBuilder {
  /**
   * @var array $toolboxInfo
   *   The entity type toolbox info.
   */
  protected $toolboxInfo = array();

  /** {{@inheritdoc}} */
  public function __construct($entityType, $tableKey = NULL) {
    parent::__construct($entityType, $tableKey);
    $this->toolboxInfo = entity_toolbox_get_info($this->entityType);
  }
}