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
  public function __construct($entityType, $tableKey, array $rawData) {
    parent::__construct($entityType, $tableKey, $rawData);
    $this->toolboxInfo = entity_toolbox_get_info($this->entityType);
  }
}