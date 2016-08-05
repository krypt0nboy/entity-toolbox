<?php


/**
 * Class HookBuilder
 *
 * Used to build a hook data.
 */
class HookBuilder extends BuilderBase {
  /**
   * @var null|string $hook
   *   The hook for which the data is built/rebuilt.
   */
  protected $hook;
  /**
   * @var array $hookInfo
   *   The hook info declared in entity toolbox.
   *
   * @see hook_hook_register_info().
   */
  protected $hookInfo = array();

  /**
   * HookBuilder constructor.
   *
   * @param string $hook
   *   The hook for which the data is built/rebuilt.
   * @param string $entityType
   *   The entity type.
   *
   * @throws EntityToolboxException
   */
  public function __construct($hook = NULL, $entityType = NULL, array $rawData = array()) {
    parent::__construct($entityType, $rawData);
    if (!isset($hook)) {
      throw new HookNameNotProvided();
    }
    $this->hook     = $hook;
    $this->hookInfo = entity_toolbox_hook_get_info($this->hook);
  }

  /** {{@inheritdoc}} */
  public function build() {

  }
}